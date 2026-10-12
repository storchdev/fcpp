# 027.01 — Reference members bound to temporaries: constructor parameter: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none at `-O0`; at `-O2` `-Wdangling-pointer=` and `-Wuninitialized` (inside `<bits/basic_string.h>`) | none at either level |
| No sanitizer | prints `[` + garbage + `] started` at both levels | prints `[` + garbage + `] started` at both levels |
| ASan `-O0`, `-O1`, `-O2` | `stack-use-after-scope` | `stack-use-after-scope` |
