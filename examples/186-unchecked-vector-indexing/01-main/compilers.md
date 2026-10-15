# 186 — Unchecked vector indexing: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++11 -Wall -Wextra`, `-O0` and `-O2`; AddressSanitizer at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings, `-O0` | none | none |
| Warnings, `-O2` | `-Warray-bounds` | none |
| Output, `-O0` | libstdc++ assertion abort: index must be less than size | libstdc++ assertion abort: index must be less than size |
| Output, `-O2` | `0` in this run | garbage value in this run |
| AddressSanitizer, `-O1` | `heap-buffer-overflow`; exit 1 | `heap-buffer-overflow`; exit 1 |
