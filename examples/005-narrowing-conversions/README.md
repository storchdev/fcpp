# 005 — Narrowing conversions

Braced initialization makes narrowing conversions (ones that can change the value) ill-formed ([dcl.init.list]); every other initialization form accepts them silently. The two cases show both sides.

| Case | What it shows |
| --- | --- |
| `01-brace-rejects-narrowing` | `T x{value}` refuses lossy conversions, with a compile error from both g++ and clang++ for constants, and a difference between them for non-constants. |
| `02-silent-without-braces` | `T x = value;` / `T x(value);` truncate, wrap, or round with no diagnostic from `-Wall -Wextra` (g++ only warns for the constant `300`). |

Mental model: braces are a lint for conversions. Use them to make the compiler check, and spell out intended narrowing with `static_cast`, `std::lround`, or `std::in_range`.
