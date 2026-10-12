# 173 — `std::unordered_map` performance assumptions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Constant hash, `-O0` and `-O2` | slow (times in `explanation.md`) | slow (times in `explanation.md`) |
