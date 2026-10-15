# 188 — Accidental switch fallthrough: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++11 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings, `-Wall -Wextra` | `-Wimplicit-fallthrough` | none |
| Warnings, explicit `-Wimplicit-fallthrough` | `-Wimplicit-fallthrough` | `-Wimplicit-fallthrough` |
| Output, `-O0` and `-O2` | `12` | `12` |
