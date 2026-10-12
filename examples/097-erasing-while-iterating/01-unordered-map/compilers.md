# 097.01 — Erasing while iterating: `unordered_map`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Run without sanitizer, `-O0` and `-O2` | crashes (core dumped) | crashes (core dumped) |
| ASan, `-O0`, `-O1`, `-O2` | `heap-use-after-free` | `heap-use-after-free` |
| Scratch test: same loop over `std::map`, under ASan | ran to completion (`size=5`) | ran to completion (`size=5`) |
