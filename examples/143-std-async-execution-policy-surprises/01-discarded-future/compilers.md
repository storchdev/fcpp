# 143.01 — `std::async` execution policy surprises: discarded future: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference in kind: both compilers warn with `[-Wunused-result]` (different wording) at `-O0` and `-O2`, and both print `task finished` before `launched`.

