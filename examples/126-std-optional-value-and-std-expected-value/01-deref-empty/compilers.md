# 126.01 — `std::optional::value()` and `std::expected::value()`: dereferencing an empty optional: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** Only run-time behavior differs between the compilers.

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Plain run `-O0` | aborts: libstdc++ assertion `this->_M_is_engaged()` | same |
| Plain run `-O2` | `length = 0` | an empty line |

