# 005.02 — Narrowing conversions: silent outside braces: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Build, `-O0` and `-O2` | builds | builds |
| Output, `-O0` and `-O2` | `percent=99 level=44 id=705032704 f=16777216.0` | same |
| Warning, line 9 (`300` to `uint8_t`) | `-Woverflow`: `unsigned conversion from 'int' to 'uint8_t' ... changes value from '300' to '44'` | `-Wconstant-conversion` |
| Warning, line 12 (`int` to `float`, 16777217 to 16777216) | none under `-Wall -Wextra` | `-Wimplicit-const-int-float-conversion` |
