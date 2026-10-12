# 075.02 — Name hiding in inheritance: silently selected function: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns (also not with `-Woverloaded-virtual -Wshadow`), and both print `Derived::f(double)` then `Base::f(int)` at `-O0` and `-O2`.
