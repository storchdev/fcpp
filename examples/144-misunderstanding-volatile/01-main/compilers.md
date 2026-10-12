# 144 — Misunderstanding `volatile`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).** No difference in kind: neither compiler warns, both lose updates at `-O0` and `-O2`, and TSan reports `data race` at `-O0`, `-O1` and `-O2` with both.

