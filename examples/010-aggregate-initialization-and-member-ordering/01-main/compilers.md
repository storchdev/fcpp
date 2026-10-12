# 010 — Aggregate initialization and member ordering: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** Both print `a: 800x600 border=2`, `b: 2x600 border=800`, `c: 0x600 border=800` at both levels. Both warn about the missing trailing member on line 15 (g++: `missing initializer for member 'after::Window::width' [-Wmissing-field-initializers]`; clang++: `missing field 'width' initializer [-Wmissing-field-initializers]`), and neither warns about the reordered members.
