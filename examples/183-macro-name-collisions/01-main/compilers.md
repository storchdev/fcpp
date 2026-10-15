# 183 — Macro name collisions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++98 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Errors, `-O0` and `-O2` | `macro ‘max’ requires 2 arguments, but only 1 given` | `too few arguments provided to function-like macro invocation` |
| Output, `-O0` and `-O2` | no executable | no executable |
