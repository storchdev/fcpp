# 028.01 — `std::string_view` dangling references: a view of a temporary string: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings, `-O0` and `-O2` | none | none |
| Output without sanitizer, `-O0` and `-O2` | garbage in place of the text (`... (44 chars)` with leading garbage bytes) | same |
| ASan, `-O0`, `-O1`, `-O2` | `heap-use-after-free` | `heap-use-after-free` |
