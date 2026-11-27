# benjohnbill.github.io — study notes

The terms that written pages under `study/` use. Each term is written in
English, exactly as spelled here, in every page, Korean text included. Korean
particles attach to the English word ("client가", "RST를"). A term is never
translated. Rule: `AGENTS.md` § Site rules, "Terms" (user said 2026-11-20).

## Language

### Connections (week13)

**client**:
The program that connects to a server; in the week13 lab, usually `nc`.
_Avoid_: 손님, 클라이언트, 클라

**FIN**:
The packet a kernel sends when its app closes the connection or dies: "I send no more". The other app sees it as `read` returning 0.
_Avoid_: "끝" 신호, 종료 신호

**RST**:
The packet a kernel sends back when data arrives for a connection that no app holds, or for a port where nobody listens. It removes the connection at once.
_Avoid_: 거절 신호, 리셋 신호

**SYN**:
The packet that asks for a new connection.
_Avoid_: 연결 요청

**Accept Queue**:
The line of connections the kernel has finished and the server app has not yet taken with `accept`.
_Avoid_: accept 대기열, 대기열, 기다리는 자리

**backlog**:
The second argument of `listen`: the upper limit of the Accept Queue.
_Avoid_: 백로그, 대기열 크기

**Receive Buffer**:
Per connection, where the kernel keeps received bytes until the app calls `read`.
_Avoid_: 수신 버퍼

**Send Buffer**:
Per connection, where `write` puts bytes for the kernel to send. A successful `write` means only that the bytes are here.
_Avoid_: 송신 버퍼

**old connection**:
A connection whose app has ended on at least one side but that the kernel still keeps (`TIME-WAIT`, `FIN-WAIT-2`, `CLOSE-WAIT`). On the server side it holds the port.
_Avoid_: 옛 연결, 남은 연결

### Processes

**signal**:
A notice the kernel sends to a process, for example `SIGPIPE`. Distinct from a packet, which travels between kernels.
_Avoid_: 신호, 시그널

**exit code**:
The number a process leaves when it ends. A process killed by a signal leaves 128 + the signal number.
_Avoid_: 종료 코드, 리턴 코드

### Crawlers and defenses (week13)

**bot**:
A program that sends HTTP requests with no person at each step. A crawler is one kind of bot.
_Avoid_: 봇, 로봇, 자동 프로그램

**layer**:
One group of defenses that asks the client the same question (cost, request, identity, volume, test, deal). The crawler page numbers them layer 0 to layer 5.
_Avoid_: 층, 계층, 단계, band

**crawler**:
A bot that fetches many pages, follows their links, and keeps what it reads (for a search index or for AI training data). It can obey robots.txt or ignore it.
_Avoid_: 크롤러, 크롤링 봇, 수집기, spider, 스파이더

**robots.txt**:
A text file at the root of a site that asks crawlers to stay out of some paths. RFC 9309 (2022) defines it. It is a request, not a lock.
_Avoid_: 로봇 배제 파일, 로봇 텍스트

**User-Agent**:
The HTTP request header in which the client names its own software. The client writes it freely, so it is a claim, not a proof.
_Avoid_: 유저 에이전트, UA (in prose), 브라우저 이름

**TLS fingerprint**:
A string made from the fields of the TLS ClientHello that a client sends before any HTTP byte. It identifies the TLS library, not the person.
_Avoid_: TLS 지문, 핑거프린트, 지문

**JA4**:
One format of TLS fingerprint (FoxIO). It sorts the ciphers and extensions before it hashes, so a shuffled order gives the same value. JA3 (2017) is the older format that hashes them in wire order.
_Avoid_: JA4 지문, 제이에이포

**reverse DNS**:
A check of a client IP: look up the name of the IP, check the domain (for example `googlebot.com`), then look up that name and check it gives the same IP.
_Avoid_: 역방향 DNS, 역DNS, rDNS (in prose)

**rate limit**:
A rule that rejects a client after N requests in a time window, usually with HTTP 429. The key is often the IP address, sometimes an account or API key.
_Avoid_: 속도 제한, 요청 제한, throttle, 스로틀

**residential proxy**:
A paid network that sends a crawler's requests out through the IP addresses of home and mobile connections, so each request can come from a different household.
_Avoid_: 주거용 프록시, 가정용 프록시, 레지덴셜 프록시

**headless browser**:
A real browser engine (for example Chrome) that runs with no screen and is driven by a program. It runs JavaScript and sends real browser bytes.
_Avoid_: 헤드리스 브라우저, 무화면 브라우저

**proof of work**:
A challenge that makes the client spend CPU before the server answers: find a number whose hash starts with N zeros. Anubis is one tool.
_Avoid_: 작업 증명, PoW (in prose), 계산 시험

**CAPTCHA**:
A test that a person is meant to pass and a program is meant to fail, for example an image puzzle.
_Avoid_: 캡차, 보안 문자

**tarpit**:
A response that holds a flagged client: it sends bytes very slowly or never answers, so the connection stays open and the client wastes time.
_Avoid_: 타르핏, 끈끈이, 늪

**honeypot**:
A link or path that no person reaches (hidden or disallowed in robots.txt). A client that requests it shows that it is a bot.
_Avoid_: 허니팟, 함정, 미끼

**crawl-to-refer ratio**:
For one company, the number of pages its crawlers fetch for each visitor its products send back to the site. Cloudflare publishes it.
_Avoid_: 크롤링 대 유입 비율, 수집 대비 방문 비율

### Web server (week13)

The team repository `mini-webserver` defines the last two terms. This file spells them the same way.

**Reverse Proxy**:
A server that takes the client's request in front of another server (the upstream), and sends it on or answers from its cache. The client sees only the Reverse Proxy.
_Avoid_: 리버스 프록시, 역방향 프록시

**upstream**:
The server behind a Reverse Proxy that makes the real response. In `mini-webserver`, `proxy_fetch` connects to it.
_Avoid_: 원 서버, 오리진, origin

**cache**:
In this page, the store of the Reverse Proxy: a key (method and path) maps to a full upstream reply that it can send again. A request whose key is not there is a cache miss.
_Avoid_: 캐시, 캐싱, 저장소

**Concurrency model**:
The method that the server uses to serve more than one connection at the same time: `iter`, `fork`, `pool`, or `epoll`.
_Avoid_: 동시성 모델, mode, strategy

**Worker**:
An execution unit (a thread or a process) that serves one connection at a time. In `iter` the main loop is the only Worker. `epoll` has no Worker.
_Avoid_: 워커, thread (for a Worker of any model), handler

### Neural networks (week14-15)

In these pages, "layer" means a neural network layer, not a crawler-defense layer.

**neuron**:
One unit of a layer. It holds one number for each input image: its activation.
_Avoid_: 뉴런, 노드, 신경 세포

**layer**:
In a neural network, one step that turns the activations of the previous layer into new activations. In `mnist`, an `Affine` and the `ReLU` after it.
_Avoid_: 층, 계층

**hidden layer**:
A layer between the input and the output. `TwoLayerNet` has one, with 128 neurons.
_Avoid_: 은닉층, 숨은 층

**weight**:
The number on one connection between two neurons. One layer keeps its weights in one matrix, `W`.
_Avoid_: 가중치, 웨이트

**activation**:
The number that a neuron holds after its layer runs.
_Avoid_: 활성화, 활성화 값, 활성값

**activation function**:
The function that a layer applies to each value after the weighted sum: sigmoid or `ReLU`.
_Avoid_: 활성화 함수

**sigmoid**:
The activation function `1 / (1 + exp(-x))`. It puts each value between 0 and 1. The 3Blue1Brown video uses it; `mnist` does not.
_Avoid_: 시그모이드, 로지스틱 함수

**ReLU**:
The activation function `max(0, x)`, the class `ReLU` in `mnist`.
_Avoid_: 렐루, 램프 함수

**Affine**:
The `mnist` layer class that computes `x @ W + b`.
_Avoid_: 아핀, 완전연결층, fully connected layer

**logits**:
The output of the last `Affine`: one score per class, not a probability. It can be negative or above 1.
_Avoid_: 로짓, 점수 벡터

**softmax**:
The function that turns one row of logits into probabilities that sum to 1. It keeps the order of the values.
_Avoid_: 소프트맥스

**batch**:
The images that one forward pass handles together. In `mnist`, they are the rows of `x`: `(batch_size, 784)`.
_Avoid_: 배치, 묶음

**shape**:
The size of each axis of a NumPy array, for example `(784, 128)`.
_Avoid_: 모양, 형상, 차원

**loss**:
One number that tells how far the predictions are from the correct labels. Training makes it smaller.
_Avoid_: 손실, 오차, 비용
