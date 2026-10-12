# 148.02 — Lock-free vs. wait-free guarantees: CAS retries: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference in kind: neither compiler warns, and both print `counter = 800000` with hundreds of thousands of retries for the worst thread at `-O0` and `-O2` (exact numbers vary per run).

