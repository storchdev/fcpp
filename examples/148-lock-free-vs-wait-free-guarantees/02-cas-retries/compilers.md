# 148.02 — Lock-free vs. wait-free guarantees: CAS retries: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `counter = 800000`, hundreds of thousands of retries for the worst thread (exact numbers vary per run) | `counter = 800000`, hundreds of thousands of retries for the worst thread (exact numbers vary per run) |
