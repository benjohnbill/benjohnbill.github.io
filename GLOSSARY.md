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
