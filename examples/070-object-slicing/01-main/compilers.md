# 070 — Object slicing: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `by value: Shape` and `in vector: Shape` at `-O0` and `-O2`. `clang-tidy` (`cppcoreguidelines-slicing`) is the only tool that reported it. In a scratch test with the copy constructor deleted, both compilers rejected the by-value call.
