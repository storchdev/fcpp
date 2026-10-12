# 002 — The most vexing parse: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference in behavior: both build the program, both print `t is a function: 1` at `-O0` and `-O2`, and both emit one `[-Wvexing-parse]` warning at line 16 (g++: `parentheses were disambiguated as a function declaration`; clang++: the same text).
