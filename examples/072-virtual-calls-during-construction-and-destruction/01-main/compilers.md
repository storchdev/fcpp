# 072 — Virtual calls during construction and destruction: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `Base ctor: Base`, `main: Derived`, `Base dtor: Base` at `-O0` and `-O2`. Only `clang-tidy` (`clang-analyzer-optin.cplusplus.VirtualCall`) reported it.
