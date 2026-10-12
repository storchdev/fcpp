# 060.01 — Integer division corner cases: `INT_MIN / -1`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=undefined`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Plain run, `-O0` and `-O2` | killed, core dumped | killed, core dumped |
| UBSan, `-O0`, `-O1`, `-O2` | `runtime error: division of -2147483648 by -1 cannot be represented in type 'int'`, then the process dies of SIGFPE (exit status 136) | the same `runtime error` line plus a `SUMMARY` line, then `UndefinedBehaviorSanitizer: FPE` and exit status 1 |
