# 136 — Invalid compare-exchange memory orders: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** g++ warns only at `-O0`; the run-time behavior is the same on both.

| | g++ | clang++ |
| --- | --- | --- |
| Warning `-O0` | "invalid failure memory model ‘memory_order_release’ ..." `[-Winvalid-memory-model]` | none |
| Warning `-O2` | none | none |
| Plain run `-O0` | aborts on a libstdc++ assertion | same |
| Plain run `-O2` | `ok = 1` | `ok = 1` |

