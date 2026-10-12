# 028.01 — `std::string_view` dangling references: a view of a temporary string: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).** Neither compiler warns at either level. Both print garbage in place of the text (`... (44 chars)` with leading garbage bytes) at `-O0` and `-O2`, and ASan reports `heap-use-after-free` under both compilers at `-O0`, `-O1` and `-O2`.
