# 164 — `inline` functions and variables across translation units: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings, each file compiled | none | none |
| Link, `-O0` and `-O2` | fails: ``multiple definition of `twice(int)'`` | fails: ``multiple definition of `twice(int)'`` |
| Wrapper line | `collect2: error: ld returned 1 exit status` | `clang++: error: linker command failed with exit code 1` |
