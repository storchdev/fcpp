# 095 — `std::unordered_map` rehashing: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `buckets 29 -> 127, size = 120, ref = 7` and `elements visited from the saved iterator: 63` | `buckets 29 -> 127, size = 120, ref = 7` and `elements visited from the saved iterator: 63` |
