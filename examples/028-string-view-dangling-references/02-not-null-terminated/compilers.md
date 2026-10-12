# 028.02 — `std::string_view` dangling references: not null-terminated: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).** Neither compiler warns. Both print `abc` without a sanitizer. ASan reports an overflow in every run, but the kind differs: g++ `stack-buffer-overflow` at `-O0`, `-O1`, `-O2`; clang++ `stack-buffer-overflow` at `-O0` and `global-buffer-overflow` at `-O1` and `-O2`.
