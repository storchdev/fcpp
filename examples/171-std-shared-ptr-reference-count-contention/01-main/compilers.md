# 171 — `std::shared_ptr` reference-count contention: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference in kind; both compilers show more than a 10x gap at `-O0` and `-O2` (times in `explanation.md`).

