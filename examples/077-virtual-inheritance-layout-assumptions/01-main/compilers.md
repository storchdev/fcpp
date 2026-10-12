# 077 — Virtual inheritance layout assumptions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `sizeof(L)=16 sizeof(D)=40`, `offset of V in standalone L = 12, in L-inside-D = 32` and `guess == real: 0, real->v = 7` at `-O0` and `-O2`.
