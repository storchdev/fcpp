# 066.01 — Operator precedence vs. evaluation order: `&` against `==`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | `-Wparentheses`: "suggest parentheses around comparison in operand of ‘&’" | `-Wparentheses`: "& has lower precedence than ==; == will be evaluated first" |
| Output at `-O0` and `-O2` | `bit 2 is set (wrong)` | `bit 2 is set (wrong)` |
