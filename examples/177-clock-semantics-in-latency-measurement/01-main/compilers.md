# 177 — Clock semantics in latency measurement: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both report `high_resolution_clock` as a non-steady alias of `system_clock` (both link libstdc++).

