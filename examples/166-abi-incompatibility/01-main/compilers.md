# 166 — ABI incompatibility: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: both compile each file without warnings and fail at link time with `undefined reference to `greeting[abi:cxx11]()'`.

