# 075.01 — Name hiding in inheritance: hidden overloads: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** Both reject `bad.cpp` at `-O0` and `-O2`:

| | g++ | clang++ |
| --- | --- | --- |
| Error | "cannot convert ‘const char [2]’ to ‘double’" | "cannot initialize a parameter of type 'double' with an lvalue of type 'const char[2]'" |
