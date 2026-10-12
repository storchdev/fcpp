# 072 — Virtual calls during construction and destruction: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `Base ctor: Base`, `main: Derived`, `Base dtor: Base` | same |
| `clang-tidy` `clang-analyzer-optin.cplusplus.VirtualCall` | reported it (the only tool that did) | reported it (the only tool that did) |
