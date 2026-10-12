# 047.02 — Placement new and object replacement: reusing storage without destroying: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).** Neither compiler warns, and both print `another-long-enough-string-to-defeat-sso-012345` without a sanitizer. ASan's LeakSanitizer reports `detected memory leaks` under both compilers at `-O0`, `-O1` and `-O2`.
