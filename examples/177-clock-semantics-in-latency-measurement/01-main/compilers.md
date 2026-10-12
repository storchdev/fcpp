# 177 — Clock semantics in latency measurement: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| `high_resolution_clock` | non-steady alias of `system_clock` | non-steady alias of `system_clock` |
| Standard library | libstdc++ | libstdc++ |
