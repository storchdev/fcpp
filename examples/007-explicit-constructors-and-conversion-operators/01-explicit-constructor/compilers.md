# 007.01 — `explicit` constructors: `return {...}` and copy-initialization: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Result, `-O0` and `-O2` | rejected, one error at `return {0, 0};` | rejected, one error at `return {0, 0};` |
| Error text | `converting to 'Point' from initializer list would use explicit constructor 'Point::Point(int, int)'` | `chosen constructor is explicit in copy-initialization` |
