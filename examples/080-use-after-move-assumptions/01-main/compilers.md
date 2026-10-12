# 080 — Use-after-move assumptions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `sent 'hello'`, `after move: text size=0 priority=7 pending=1`, `sent ''` | `sent 'hello'`, `after move: text size=0 priority=7 pending=1`, `sent ''` |
| `clang-tidy` `bugprone-use-after-move` | reported it (the only tool that did) | reported it (the only tool that did) |
