# 147 — `std::atomic_ref` lifetime and alignment: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| TSan, `-O0`, `-O1`, `-O2` | `data race` | `data race` |
| TSan summary, `-O2` | points into libstdc++'s thread code | not recorded |
