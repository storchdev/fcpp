# 121.01 — Throwing from destructors: during unwinding: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No warning on either compiler. Both abort with `terminate called after throwing an instance of ...` (core dumped), but the exception named differs.

| | g++ | clang++ |
| --- | --- | --- |
| Named exception at `-O0` | `std::runtime_error` | `std::runtime_error` |
| Named exception at `-O1`, `-O2` | `std::logic_error` | `std::runtime_error` |

