# 126.02 — `std::optional::value()` and `std::expected::value()`: `expected::value()` throws: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++23` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both abort with the `bad_expected_access` terminate message at `-O0` and `-O2`.

