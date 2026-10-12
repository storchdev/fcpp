# 099.02 — `insert`, `emplace`, and `try_emplace` semantics: `insert` consumes its argument: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `job is gone (null)` | `job is gone (null)` |
| Scratch test: `emplace` / `try_emplace` with an existing key | kept their `unique_ptr` argument | kept their `unique_ptr` argument |
