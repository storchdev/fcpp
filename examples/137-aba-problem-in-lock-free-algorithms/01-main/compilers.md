# 137 — ABA problem in lock-free algorithms: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `first pop returned node 0; head is now node 1 (node 2 expected)` at `-O0` and `-O2`.

