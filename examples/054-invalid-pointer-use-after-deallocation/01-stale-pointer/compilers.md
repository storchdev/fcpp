# 054 — Invalid pointer use after deallocation: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer, `-O0` | `session` and `1647090827` (one specific run) | `session` and `1525072165` (one specific run) |
| Output without sanitizer, `-O2` | `session` and `1573338488` (one specific run) | `session` and `1326778840` (one specific run) |
| ASan, every level | `heap-use-after-free` | `heap-use-after-free` |
