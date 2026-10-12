# 066.02 — Operator precedence vs. evaluation order: calls inside one expression: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output for this expression, `-O0` and `-O2` | `a b c -> 7` | `a b c -> 7` |
| Same three calls as arguments of `sum3(...)`, `-O0` and `-O2` (scratch test, see case 065) | printed `c b a` | printed `a b c` |
