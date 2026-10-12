# 143.01 — `std::async` execution policy surprises: discarded future: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings, `-O0` and `-O2` | `-Wunused-result` | `-Wunused-result` (different wording) |
| Output, `-O0` and `-O2` | `task finished` before `launched` | `task finished` before `launched` |
