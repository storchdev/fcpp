# 062.02 — Truncation and overflow during numeric casts: integer narrowing and sign changes: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** Both print `narrowed = -1294967296`, `n = 18446744073709551615, n > v.size() = 1` and `c = 44` at `-O0` and `-O2`, and neither warns under `-Wall -Wextra`. The opt-in diagnostics differ in name:

| | g++ | clang++ |
| --- | --- | --- |
| `long long` to `int` (line 8) | `-Wconversion` | `-Wshorten-64-to-32` |
| `int` to `std::size_t` (line 13) | `-Wsign-conversion` | `-Wsign-conversion` |
| `int` to `unsigned char` (line 16) | `-Wconversion` | `-Wimplicit-int-conversion` |
| `-fsanitize=implicit-conversion` | rejected: `unrecognized argument to ‘-fsanitize=’ option` | reports lines 8, 13 and 16 at run time |

With `-std=c++20 -Wall -Wextra -fsanitize=undefined` both print the same three lines of output and neither sanitizer reports anything.
