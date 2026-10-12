# 094.02 — `std::deque` invalidation rules: iterator across `push_back`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).** No difference: neither compiler warns, both crash (core dumped) in a plain run at `-O0` and `-O2`, and ASan reports `heap-use-after-free` at `-O0`, `-O1` and `-O2` with both.
