# 173 — `std::unordered_map` performance assumptions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference in kind; both compilers are slow with the constant hash at `-O0` and `-O2` (times in `explanation.md`).
