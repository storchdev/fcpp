# 137 — ABA problem in lock-free algorithms: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `first pop returned node 0; head is now node 1 (node 2 expected)` | `first pop returned node 0; head is now node 1 (node 2 expected)` |
