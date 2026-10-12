# 159.02 — `std::any` and `std::variant` runtime type assumptions: `any_cast`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** Both throw; only g++ warns, and only at `-O2`.

| | g++ | clang++ |
| --- | --- | --- |
| Warnings `-O0` | none | none |
| Warnings `-O2` | `array subscript ‘const std::__cxx11::basic_string<char>[0]’ is partly outside array bounds of ‘void [6]’` | none |
| Plain run `-O0`, `-O2` | `bad_any_cast: bad any_cast` | `bad_any_cast: bad any_cast` |
