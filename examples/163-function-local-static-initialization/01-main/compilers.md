# 163 — Function-local static initialization: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Run, `-O0` and `-O2` | aborts with `recursive_init_error` | aborts with `recursive_init_error` |
