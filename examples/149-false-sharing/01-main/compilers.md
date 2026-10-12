# 149 — False sharing: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference in kind: neither compiler warns and both show a large slowdown for the adjacent layout at `-O0` and `-O2`; see the measured ranges above (machine and load dependent).
