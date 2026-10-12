# 074 — Default arguments on virtual functions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `Derived::greet(1)` then `Derived::greet(5)` at `-O0` and `-O2`. Only `clang-tidy` (`google-default-arguments`) reported it.
