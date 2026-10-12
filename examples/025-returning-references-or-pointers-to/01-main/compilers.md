# 025 — Returning references or pointers to local objects: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, AddressSanitizer with `detect_stack_use_after_return=1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warning on `make_greeting` (`return s;`) | `-Wreturn-local-addr` (`reference to local variable 's' returned`) | `-Wreturn-stack-address` (`reference to stack memory associated with local variable 's' returned`) |
| Warning on `make_tag` (`return t.c_str();`) | none | `-Wreturn-stack-address` (`address of stack memory associated with local variable 't' returned`) |
| `-Wdangling-reference` | fires at `main` line 18 (`possibly dangling reference to a temporary`), pointing at the temporary `std::string` built from `"world"`, not at the dead local | `-Wdangling-reference` is rejected (`unknown warning option '-Wdangling-reference'`); no corresponding warning |
| ASan at `-O1` | `SEGV on unknown address 0x000000000000`, a read at line 19 | `stack-use-after-scope` at line 19 |
| ASan at `-O0` | `SEGV` at line 19 (same) | `stack-use-after-return` at line 19 |
| No sanitizer, `-O0` | crashes before printing anything | prints garbage bytes for the first line, then `tag-42` |
| No sanitizer, `-O2` | crashes before printing anything | prints `hello, world` then `world` |

the g++ ASan report is a read of address `0x000000000000`, so g++ evidently replaced the returned dangling address with null and the program dies on a null read instead of reading freed stack; clang++ leaves the dangling address in place, so ASan reports a stack error and an unsanitized build may even print the "right" text. No heap-use-after-free report appeared with either compiler. (I did not check why clang++ printed `world` for the second line at `-O2`; with UB, either result is permitted.)
