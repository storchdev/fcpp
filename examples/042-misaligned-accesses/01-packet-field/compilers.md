# 042 — Misaligned accesses: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=undefined`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer, `-O0` and `-O2` | `16` | `16` |
| UBSan, `-O0`, `-O1`, `-O2` | `load of misaligned address ... for type 'const uint32_t', which requires 4 byte alignment` (line 8 col 59) | same message (line 8 col 12) |
