# 054 — Invalid pointer use after deallocation: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).** Neither compiler warns. Without a sanitizer both print `session` followed by a garbage number (different per compiler and level: `1647090827` and `1573338488` with g++, `1525072165` and `1326778840` with clang++ at `-O0` and `-O2`). ASan reports `heap-use-after-free` under both compilers at every level.
