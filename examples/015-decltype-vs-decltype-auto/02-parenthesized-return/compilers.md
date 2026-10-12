# 015.02 — `decltype` vs. `decltype(auto)`: a parenthesized return: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address` with `detect_stack_use_after_return=1`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warning (line 9) | `-Wreturn-local-addr` (`reference to local variable 'id' returned`) | `-Wreturn-stack-address` (`reference to stack memory associated with local variable 'id' returned`) |
| No sanitizer, `-O0` | crashes (core dumped) | prints `42` |
| No sanitizer, `-O2` | crashes (core dumped) | prints `-1920482584` (garbage; varies) |
| ASan `-O0` | `SEGV on unknown address 0x000000000000` | `stack-use-after-return` |
| ASan `-O1`, `-O2` | `SEGV on unknown address 0x000000000000` (the checker's configuration) | no report in these runs |

g++ replaces the returned address of the local with null, so the program dies on a null read; clang++ keeps the dangling address, so the outcome depends on what reused the stack slot, and ASan at `-O1` and `-O2` did not flag the read. This is why the case's sanitizer is verified with g++.
