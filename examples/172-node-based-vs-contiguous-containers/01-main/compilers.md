# 172 — Node-based vs. contiguous containers: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| `list` vs `vector`, `-O0` and `-O2` | `list` much slower (times in `explanation.md`) | `list` much slower (times in `explanation.md`) |
