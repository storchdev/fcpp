# 055.02 — Over-aligned allocation and packed structures: a pointer to a packed member: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings, `-O0` and `-O2` | `-Waddress-of-packed-member` | `-Waddress-of-packed-member` |
| Output, `-O0` and `-O2` | `3` | `3` |
| Sanitizer header | none set (see `explanation.md` for the g++ UBSan gap) | none set |
