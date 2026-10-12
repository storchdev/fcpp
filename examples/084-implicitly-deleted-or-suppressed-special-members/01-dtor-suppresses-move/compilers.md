# 084.01 — Implicitly deleted or suppressed special members: destructor suppresses move: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings under `-Wall -Wextra` | none | none |
| Extra flag that reports it | `-Wdeprecated-copy-dtor` | `-Wdeprecated-copy-with-user-provided-dtor` |
| Output at `-O0` and `-O2` | `move`, `copy`, `cleanup`, `cleanup` | same |
