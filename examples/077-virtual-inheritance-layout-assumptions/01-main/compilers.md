# 077 — Virtual inheritance layout assumptions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `sizeof(L)=16 sizeof(D)=40`, `offset of V in standalone L = 12, in L-inside-D = 32` and `guess == real: 0, real->v = 7` | `sizeof(L)=16 sizeof(D)=40`, `offset of V in standalone L = 12, in L-inside-D = 32` and `guess == real: 0, real->v = 7` |
