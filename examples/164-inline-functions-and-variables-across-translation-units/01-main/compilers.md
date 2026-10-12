# 164 — `inline` functions and variables across translation units: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: both compile each file without warnings and fail at link time (`-O0` and `-O2`) with the linker message `multiple definition of `twice(int)'`; the wrapper line differs (`collect2: error: ld returned 1 exit status` vs `clang++: error: linker command failed with exit code 1`).

