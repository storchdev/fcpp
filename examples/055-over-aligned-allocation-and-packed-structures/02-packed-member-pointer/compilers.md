# 055.02 — Over-aligned allocation and packed structures: a pointer to a packed member: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** Both compilers warn with `-Waddress-of-packed-member` at `-O0` and `-O2` and both print `3`. No sanitizer header is set for this case (see `explanation.md` for the g++ UBSan gap).
