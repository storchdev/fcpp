# 047.02 — Placement new and object replacement: reusing storage without destroying: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer | `another-long-enough-string-to-defeat-sso-012345` | same |
| ASan (LeakSanitizer), `-O0`, `-O1`, `-O2` | `detected memory leaks` | `detected memory leaks` |
