# 049 — `memcpy` on non-trivial types: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warning | `-Wclass-memaccess` at `-O0` and `-O2` | `-Wnontrivial-memcall` at `-O0` and `-O2` |
| No sanitizer | `free(): double free detected in tcache 2`, then aborts | same message, then aborts |
| ASan `-O0`, `-O1`, `-O2` | `attempting double-free` | `attempting double-free` |

Both warn and both detect the double free, with different flag names.
