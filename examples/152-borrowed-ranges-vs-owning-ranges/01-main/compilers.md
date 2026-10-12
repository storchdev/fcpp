# 152 — Borrowed ranges vs. owning ranges: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20` `-Wall -Wextra`, `-O0` and `-O2`).** No difference in outcome: both reject `bad.cpp` at `-O0` and `-O2`; the diagnostic wording differs as quoted in `explanation.md`.

