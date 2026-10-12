# 148.01 — Lock-free vs. wait-free guarantees: non-lock-free atomic: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** | | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Link `-O0`, `-O2` | links | `undefined reference to `__atomic_is_lock_free'` |
| Plain run | `atomic<Big> is_lock_free = 0, atomic<long> is_lock_free = 1` | not built (with `-latomic`: same line) |

