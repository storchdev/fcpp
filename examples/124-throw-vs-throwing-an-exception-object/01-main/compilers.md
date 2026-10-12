# 124 — `throw;` vs. throwing an exception object: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `outer: plain exception, what() = std::exception` | `outer: plain exception, what() = std::exception` |
