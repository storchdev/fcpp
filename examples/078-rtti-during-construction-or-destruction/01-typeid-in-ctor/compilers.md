# 078.01 — RTTI during construction or destruction: `typeid` in a constructor: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `typeid in Base ctor: 4Base`, `dynamic_cast<Derived*>(this) in Base ctor: (nil)` and `typeid after construction: 7Derived` at `-O0` and `-O2`.
