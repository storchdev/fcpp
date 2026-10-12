# 007.01 — `explicit` constructors: `return {...}` and copy-initialization: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** Both compilers reject the program with one error at the `return {0, 0};` line, at both levels. g++: `converting to 'Point' from initializer list would use explicit constructor 'Point::Point(int, int)'`. clang++: `chosen constructor is explicit in copy-initialization`.
