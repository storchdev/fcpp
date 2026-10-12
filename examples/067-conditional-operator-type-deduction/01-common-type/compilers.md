# 067.01 — Conditional operator type deduction: common type of the branches: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings under `-Wall -Wextra` | none | none |
| With `-Wsign-conversion` | "conversion to ‘unsigned int’ from ‘int’ may change the sign of the result" | `-Wsign-conversion`: "operand of ? changes signedness: 'int' to 'unsigned int'" |
| Output at `-O0` and `-O2` | `m = 4294967295, m > 100 is true` | same |
