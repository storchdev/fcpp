# 176.02 — Hidden copies in range-based loops: `vector<bool>` proxy: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference in outcome: both reject `bad.cpp` at `-O0` and `-O2`; the wording is quoted in `explanation.md`.

