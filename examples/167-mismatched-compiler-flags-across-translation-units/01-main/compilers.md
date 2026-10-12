# 167 — Mismatched compiler flags across translation units: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `value = 1 (expected 16909060), sizeof(Packet) = 8` at `-O0` and `-O2`.
