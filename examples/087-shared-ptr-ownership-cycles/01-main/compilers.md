# 087 — `shared_ptr` ownership cycles: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Plain run, `-O0` and `-O2` | `a.use_count=2 b.use_count=2`, no `~Node` | same |
| LeakSanitizer `-O0` | `Indirect leak` reported | no report |
| LeakSanitizer `-O1` | `Indirect leak` reported | no report |
| LeakSanitizer `-O2` | `Indirect leak` reported | `Indirect leak` reported |
