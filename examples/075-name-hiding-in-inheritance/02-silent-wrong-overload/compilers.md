# 075.02 — Name hiding in inheritance: silently selected function: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings (also with `-Woverloaded-virtual -Wshadow`) | none | none |
| Output, `-O0` and `-O2` | `Derived::f(double)` then `Base::f(int)` | same |
