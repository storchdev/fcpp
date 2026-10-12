# 005.01 — Narrowing conversions: brace initialization rejects them: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Result, `-O0` and `-O2` | rejected, two errors | rejected, two errors |
| Error, line 9 | `narrowing conversion of '300' from 'int' to 'uint8_t' {aka 'unsigned char'} [-Wnarrowing]` | `constant expression evaluates to 300 which cannot be narrowed to type 'std::uint8_t' (aka 'unsigned char') [-Wc++11-narrowing]` |
| Error, line 10 | `narrowing conversion of '3.5e+0' from 'double' to 'int' [-Wnarrowing]` | `type 'double' cannot be narrowed to 'int' in initializer list [-Wc++11-narrowing]` |
| Extra warnings | none | `-Wliteral-conversion` (3.5 to 3), `-Wconstant-conversion` (300 to 44) |
