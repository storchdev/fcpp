# 159.01 — `std::any` and `std::variant` runtime type assumptions: variant `get`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `bad_variant_access: std::get: wrong index for variant` | `bad_variant_access: std::get: wrong index for variant` |
