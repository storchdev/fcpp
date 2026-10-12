# 070 — Object slicing: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `by value: Shape` and `in vector: Shape` | same |
| `clang-tidy` `cppcoreguidelines-slicing` | reported it (the only tool that did) | reported it (the only tool that did) |
| Scratch test with the copy constructor deleted | by-value call rejected | by-value call rejected |
