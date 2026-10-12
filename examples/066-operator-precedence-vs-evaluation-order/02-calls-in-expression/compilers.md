# 066.02 — Operator precedence vs. evaluation order: calls inside one expression: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference for this expression: neither compiler warns, and both print `a b c -> 7` at `-O0` and `-O2`. They do differ for the same three calls used as function arguments (`sum3(...)`): g++ printed `c b a`, clang++ printed `a b c`, at both levels (scratch test, see case 065).
