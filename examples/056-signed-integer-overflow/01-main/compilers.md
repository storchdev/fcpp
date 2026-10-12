# 056 — Signed integer overflow: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`; neither compiler emitted a warning at any level).** Output of `bad.cpp` as built, with `-fwrapv`, and with `-ftrapv`:

| | `will_overflow(INT_MAX)` | `count_up(INT_MAX-3)` | with `-fwrapv` | with `-ftrapv` |
| --- | --- | --- | --- | --- |
| g++ `-O0` | `0` | `4` | `1`, `4` | aborts (core dumped) |
| g++ `-O1` | `0` | `4` | `1`, `4` | no trap: `1`, `4` |
| g++ `-O2` | `0` printed over and over; `count_up`'s line is never reached, and a 2 second timeout killed it (27458 lines of output in one run) | never printed | `1`, `4` | `0` printed over and over, same as the plain build |
| clang++ `-O0` | `1` | `4` | `1`, `4` | aborts (core dumped) |
| clang++ `-O1` | `0` | `11` | `1`, `4` | aborts (core dumped) |
| clang++ `-O2` | `0` | `11` | `1`, `4` | aborts (core dumped) |

So the same source gives a wrong answer, a different wrong answer, or a program that never finishes, depending on compiler and flags. g++ `-O2` is the worst case: the program does not terminate normally and keeps repeating its first line; I did not investigate the mechanism. clang++ `-O1`/`-O2` leave `count_up` running past the wraparound until the `break` stops it at 11. `-ftrapv` caught the overflow with clang++ at every level but with g++ only at `-O0`, and the checker's `sanitize: undefined` header is the dependable detection.
