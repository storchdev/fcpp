# 095 — `std::unordered_map` rehashing: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `buckets 29 -> 127, size = 120, ref = 7` and `elements visited from the saved iterator: 63` at `-O0` and `-O2`.
