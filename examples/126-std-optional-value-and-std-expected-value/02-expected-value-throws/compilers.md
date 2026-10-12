# 126.02 — `std::optional::value()` and `std::expected::value()`: `expected::value()` throws: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++23` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Run, `-O0` and `-O2` | aborts with the `bad_expected_access` terminate message | aborts with the `bad_expected_access` terminate message |
