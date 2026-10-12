# 120.02 — Template instantiation across translation units: definition not visible: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** Both fail at link time for `bad.cpp`; the compile step alone succeeds with both at `-O0` and `-O2`.

| | g++ | clang++ |
| --- | --- | --- |
| Link error | "undefined reference to `Box<int>::get() const'" (then "ld returned 1 exit status") | "undefined reference to `Box<int>::get() const'" (then "linker command failed with exit code 1") |
