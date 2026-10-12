# 090.01 — `unique_ptr::release` vs. `reset`: `release` leaks: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Plain run, `-O0` and `-O2` | `use() returned; no ~Resource was printed` | same |
| LeakSanitizer `-O0` | `Direct leak of 32 byte(s)` | `Direct leak of 32 byte(s)` |
| LeakSanitizer `-O1`, `-O2` | `Direct leak of 32 byte(s)` | no report |
