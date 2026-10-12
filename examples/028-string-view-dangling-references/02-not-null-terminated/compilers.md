# 028.02 — `std::string_view` dangling references: not null-terminated: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer | `abc` | `abc` |
| ASan, `-O0` | `stack-buffer-overflow` | `stack-buffer-overflow` |
| ASan, `-O1` and `-O2` | `stack-buffer-overflow` | `global-buffer-overflow` |
