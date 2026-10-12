# 171 — `std::shared_ptr` reference-count contention: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Gap, `-O0` and `-O2` | more than 10x (times in `explanation.md`) | more than 10x (times in `explanation.md`) |
