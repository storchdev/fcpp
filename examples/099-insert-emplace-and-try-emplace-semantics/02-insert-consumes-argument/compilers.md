# 099.02 — `insert`, `emplace`, and `try_emplace` semantics: `insert` consumes its argument: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `job is gone (null)` at `-O0` and `-O2`. In a scratch test, `emplace` and `try_emplace` with an existing key kept their `unique_ptr` argument on both compilers.
