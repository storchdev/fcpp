# 102.03 — `std::vector<bool>` specialization: adjacent elements race: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer, `-O0` and `-O2` | `11` | `11` |
| TSan, `-O0`, `-O1`, `-O2` | `data race` | `data race` |
