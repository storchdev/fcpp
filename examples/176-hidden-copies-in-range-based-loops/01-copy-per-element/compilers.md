# 176.01 — Hidden copies in range-based loops: copy per element: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `copies during the loop = 1000` at `-O0` and `-O2`.

