# 014.02 — `auto` with brace initialization: multiple elements: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Result, `-O0` and `-O2` | rejected, two errors | rejected, two errors |
| Line 7, `auto x{1, 2};` | `direct-list-initialization of 'auto' requires exactly one element [-fpermissive]` | `initializer for variable 'x' with type 'auto' contains multiple expressions` |
| Line 8, `auto y = {1, 2.5};` | `unable to deduce 'std::initializer_list<auto>' from '{1, 2.5e+0}'` | `deduced conflicting types ('int' vs 'double') for initializer list element type` |
