# 074 — Default arguments on virtual functions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `Derived::greet(1)` then `Derived::greet(5)` | same |
| `clang-tidy` `google-default-arguments` | reported it (the only tool that did) | reported it (the only tool that did) |
