# 010 — Aggregate initialization and member ordering: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Output, `-O0` and `-O2` | `a: 800x600 border=2`, `b: 2x600 border=800`, `c: 0x600 border=800` | same |
| Warning, line 15 (missing trailing member) | `-Wmissing-field-initializers`: `missing initializer for member 'after::Window::width'` | `-Wmissing-field-initializers`: `missing field 'width' initializer` |
| Warning for the reordered members | none | none |
