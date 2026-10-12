# 123 — Catching polymorphic exceptions by value: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** Only g++ warns; run-time behavior is identical.

| | g++ | clang++ |
| --- | --- | --- |
| Warning | "catching polymorphic type ‘class std::exception’ by value [-Wcatch-value=]" | none |
| Output at `-O0`, `-O2` | `what() = std::exception` | `what() = std::exception` |

