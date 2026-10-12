# 047.01 — Placement new and object replacement: a misaligned arena: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=undefined`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer, `-O0` and `-O2` | `x 3.5` | `x 3.5` |
| UBSan, `-O0`, `-O1`, `-O2` | `store to misaligned address ... for type 'double', which requires 8 byte alignment` | `constructor call on misaligned address ... for type 'double', which requires 8 byte alignment` (line 17) and a misaligned load (line 18) |
