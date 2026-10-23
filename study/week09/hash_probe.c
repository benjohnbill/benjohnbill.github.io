#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define BUCKET_CNT 4
#define FNV_64_PRIME 0x00000100000001B3UL
#define FNV_64_BASIS 0xcbf29ce484222325UL

struct hash_elem {
    struct hash_elem *next;
};

typedef uint64_t hash_hash_func(const struct hash_elem *e);
typedef bool hash_less_func(const struct hash_elem *a,
                            const struct hash_elem *b);
struct hash {
    struct hash_elem *buckets[BUCKET_CNT]; /* 서랍마다 list의 첫 원소 */
    hash_hash_func *hash;                  /* 몇 번 서랍? */
    hash_less_func *less;                  /* 둘 중 누가 더 작은 지 */
};

static int less_calls; /* less가 불린 횟수(비교를 얼마나 하는 지) */

struct page {
    uint64_t va;               /* page의 시작 가상 메모리 - key */
    struct hash_elem spt_elem; /* list에 엮이는 연결점 */
};

#define hash_entry(HASH_ELEM, STRUCT, MEMBER)                                  \
    ((STRUCT *)((uint8_t *)&(HASH_ELEM)->next - offsetof(STRUCT, MEMBER.next)))

uint64_t hash_bytes(const void *buf_, size_t size)
{
    const unsigned char *buf = buf_;
    uint64_t hash;

    if (buf == NULL) {
        return -1;
    }

    hash = FNV_64_BASIS;
    while (size-- > 0) {
        hash = (hash * FNV_64_PRIME) ^ *buf++;
    }

    return hash;
}

/* 해시값을 만들어주기. */
static uint64_t page_hashing(const struct hash_elem *elem)
{
    const struct page *p = hash_entry(elem, struct page, spt_elem);
    return hash_bytes(&p->va, sizeof(p->va));
}

static bool page_less(const struct hash_elem *small,
                      const struct hash_elem *big)
{
    const struct page *less = hash_entry(small, struct page, spt_elem);
    const struct page *bigger = hash_entry(big, struct page, spt_elem);

    less_calls++; /* page끼리 비교할 때마다 count를 하나 한다 */
    return less->va < bigger->va;
}

static size_t find_index(struct hash *hash, struct hash_elem *elem)
{
    return hash->hash(elem) & (BUCKET_CNT - 1);
}

static struct hash_elem *find_elem(struct hash *hash, size_t idx,
                                   struct hash_elem *elem)
{
    struct hash_elem *i = hash->buckets[idx];
    for (; i != NULL; i = i->next) {
        if ((!hash->less(i, elem)) && (!hash->less(elem, i))) {
            return i;
        }
    }
    return NULL;
}

/* 가상 메모리에 페이지를 할당 // 기존에 할당 되어있으면 안 함 */
static struct hash_elem *hash_align(struct hash *hash, struct hash_elem *new)
{
    size_t idx = find_index(hash, new);
    struct hash_elem *old = find_elem(hash, idx, new);
    if (!old) {
        new->next = hash->buckets[idx];
        hash->buckets[idx] = new;
    }
    return old;
}

static struct hash_elem *find_same_hash(struct hash *hash,
                                        struct hash_elem *elem)
{
    return find_elem(hash, find_index(hash, elem), elem);
}

int main(void)
{
    struct hash spt = {.hash = page_hashing, .less = page_less};
    struct page pages[8];
    struct page example = {.va = 0x403000};
    struct page key;
    struct hash_elem *x;
    int i;

    /* va를 각각 SPT에 넣는다. */
    for (i = 0; i < 8; i++) {
        pages[i].va = 0x400000 + i * 0x1000;
        hash_align(&spt, &pages[i].spt_elem);
        printf("%p : 정상 할당 완료!\n", (void *)pages[i].va);
    }

    /* 중복 확인 */
    if (hash_align(&spt, &example.spt_elem)) {
        printf("%p : 중복 감지!\n", (void *)example.va);
    } else {
        printf("%p : 중복 미감지로 인해, 추가 등록!\n", (void *)example.va);
    }

    /*     round_down 을 통해 key를 만들고 있는 지 체크   */
    key.va = 0x405234 & ~(uint64_t)0xfff;
    less_calls = 0;
    x = find_same_hash(&spt, &key.spt_elem);

    if (x) {
        struct page *p = hash_entry(x, struct page, spt_elem);
        printf("fault 0x405234 -> page va %#lx (서랍 %zu, less %d번)\n",
               (unsigned long)p->va, find_index(&spt, x), less_calls);
    }

    /* 8개를 전부 다 찾았을 때 less가 불린 횟수 세기 */
    less_calls = 0;
    for (i = 0; i < 8; i++) {
        find_same_hash(&spt, &pages[i].spt_elem);
    }
    printf("BUCKET_CNT %d: 8번 탐색, less call %d번\n", BUCKET_CNT, less_calls);
    return 0;
}
