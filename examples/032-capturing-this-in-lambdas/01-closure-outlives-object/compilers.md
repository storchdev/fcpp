# 032.01 — Capturing `this` in lambdas: the closure outlives the object: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warning, line 12 (implicit `this` via `[=]`; about the deprecated capture, not the dangling pointer) | `-Wdeprecated`: `implicit capture of 'this' via '[=]' is deprecated in C++20` | `-Wdeprecated-this-capture` |
| Output without sanitizer | garbage `clicks=` value | garbage `clicks=` value |
| ASan, every level | `heap-use-after-free` | `heap-use-after-free` |
