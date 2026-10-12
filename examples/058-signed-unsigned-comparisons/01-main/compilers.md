# 058 — Signed/unsigned comparisons: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** Both warn with `-Wsign-compare` for both comparisons, with different wording, and both print `-1 < 1u is false` and `idx -1 is out of range (wrong reason)` at `-O0` and `-O2`.

| | g++ | clang++ |
| --- | --- | --- |
| `-Wsign-compare` | "comparison of integer expressions of different signedness: ‘int’ and ‘unsigned int’" | "comparison of integers of different signs: 'int' and 'unsigned int'" |
