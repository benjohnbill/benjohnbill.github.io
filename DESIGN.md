---
scope: Written notes under study/ (not the decks)
role: Design reference. A sample of formats to copy, not a full spec
source: study/week07/debug-panic-exit.html (original jingeunOS/notes/debug-panic-eli5.html)
decided: 2026-10-14, from the review rounds of that page (user said)
binding: AGENTS.md § Site rules wins on conflict. Only the "Keep" items below are firm
---

# DESIGN.md — study note reference

This file is a **reference**. It shows formats that worked: type sizes, letter
spacing, cards, fold cards, panes, heading voice. Copy them when the content
fits. The live example is
<https://benjohnbill.github.io/study/week07/debug-panic-exit.html>; read its
`<style>` block for the CSS.

Strength of each item:

| Level | Meaning |
|---|---|
| **Keep** | Do not break it. Each one came from a rejected design. |
| **Default** | Use it. To change it, write the design reason in a CSS comment. |
| **Pattern** | Use it when the content has that shape. Otherwise skip it. |

Pages made before 2026-10-14 (`oop-in-c`, `bsize-cast`, …) follow this file
only when they are edited for another reason.

---

## 1. Type — Default

| Item | Value | Why |
|---|---|---|
| Root | `html { font-size: 19px }` | One number moves the page; every size is `rem` |
| Headings | h3 1.25rem (24) · h2 1.56rem (30) · h1 1.95rem (37) | Major third, ×1.25 |
| `.lead` | 1.1rem, line-height 1.75 | A story beat: the claim of a section |
| Secondary | .85rem (16px) | 16px is the floor for Korean text |
| Code | 16px · panes 14px · logs 13px | Mono glyphs are wider; ~90 columns fit the frame |
| Line height | body 1.85 (site.css) · code 1.5–1.6 | |
| Letter spacing | browser default (0); no `letter-spacing` | Plex Sans KR is spaced for Korean already |
| Line breaks | `word-break: keep-all` (site.css); code cells `overflow-wrap: anywhere` | Korean words do not split; long log lines still fit |

Fonts come from the three slots in `site.css`: `--font-head`, `--font-body`,
`--font-code`. A chip or label uses the code slot.

## 2. Color — Keep

- Color marks meaning only. One hue ramp for versions (site `--s3`): lighter =
  farther from the machine, deeper = closer. Example: `--s3-rail` → mix → `--s3`.
- Two more colors only: green `--s2-soft` = added / only one side has it; red
  `--s1-soft` = removed.
- No per-version signature colors (rejected: "not harmonious"). No colored
  keywords in prose.
- All-neutral is also wrong when versions must be told apart. Use the ramp plus
  a ①②③ number.

## 3. Boxes — Keep

Box rules 1–5 in `AGENTS.md` § Site rules. In short: outer box = `1px solid
var(--line)`, no fill; fill one level in only; no shadow, no large radius.

## 4. Gray text — Keep

- Outside fold cards: no gray helper lines. No `.legend`, no `.meta` captions,
  no intro line, no `<small>` caption.
- Needed information goes inline in the body sentence or into a code comment.
- Gray is allowed inside code blocks (comments, dim log lines) and inside fold
  cards.

## 5. Voice — Keep

Telegraphic, noun-ending Korean. Not 해요체, not 평서체.

Exception: a `lesson` card's page (made by `/teach`) keeps sentence voice
(평서체), because a lesson explains step by step. The card label `레슨` tells the
reader the voice differs (user decided 2026-11-11).

| Place | Shape | Sample |
|---|---|---|
| h1 | The question or situation, as a noun phrase | `exit(1)을 받아 줄 OS가 없을 때` |
| `.sub` | Two clauses: what differs · where it splits | `같은 debug_panic, … 끝이 다름. 갈림길은 밑에 받아 줄 OS의 유무` |
| h2 | `N. <topic>`; a noun phrase, or `<topic>: <short question>` | `2. 공통 코드` · `3. 실제 코드: 뭐가 다를까?` · `5. 실물: Pintos와 Linux의 커널 PANIC` |
| h3 / card title | Name only, with ①②③ when it is a version | `③ Pintos 커널` |
| `.lead` | The section's claim, with `→` for cause and effect | `밑에 받아 줄 OS 있음 → exit(1) · 없음 → 스스로 꺼야 함` |
| Body line | One line; `·` separates items, `=` defines | `차이는 둘: 옵션이 켜졌을 때 Pintos는 끄고 Linux는 재시작, …` |
| Fold summary | What is inside, as a short noun phrase | `원본 로그` · `주소를 함수 이름으로` |

- A body gloss or aside outside a fold card: one line at most. A fold card may
  be longer.
- Banned words and shapes (AI slop): emoji, "Q1–Q5 궁금증" sections, empty
  memo sections, grids of six cards, family metaphors ("세 형제"), "뼈대",
  internal tool names in prose. File paths stay as they are.
- Run `node ~/.claude/skills/kill-ai-slop/scripts/scan.mjs <dir>` after edits.

## 6. Patterns — Pattern

| Pattern | Use when | Shape (class in the example page) |
|---|---|---|
| Fold card | Evidence, repro steps, raw logs: detail a reader may skip | `details.fold`: chevron, `펼치기`/`접기` chip, hover fill. The reader must see that it opens |
| Toggle panes | Two or three long listings to compare | `.panes`: one button per listing, each toggles on its own (not synced); open panes split one area; height = tallest open pane; lines wrap with a 2ch hanging indent, no horizontal scroll |
| Step table | Two systems run the same steps in the same order | `table.steps`: row = one step + tag (`같음` / `다름` / `X만`); cell = code line + the log line it printed; green cell = only one side; on a phone each row becomes a block |
| Side-by-side ends | Two short code blocks whose last lines differ | `.ends`: two columns, one column under 760px |
| Version cards | Three cases of one idea, with a small diagram | `.grid` of `.card`; SVG uses `var(--ink)`; one-line telegraphic caption |
| Summary table | Close a comparison section | Plain `table`; wrap in `.scroll` only when columns cannot shrink |

Rejected, do not bring back: synced cards (open one → all open), fixed-height
panes with vertical scroll, horizontal scroll in code panes.

## 7. Check before publish

1. Headless render at 1000px and 390px wide: no cut text, no page-level
   horizontal scroll. Then run `~/.claude/scripts/page-check/page-check <file>`
   and fix each Block before any push: it sees clipped content that a headless
   screenshot hides.
2. Slop scan (section 5).
3. Copy the original byte-for-byte to `study/weekNN/` (Site rules: Copies).
