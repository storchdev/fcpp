# 069.01 — NaN and comparison semantics: NaN as a map key: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings under `-Wall -Wextra` | none | none |
| With `-Wfloat-equal` | "comparing floating-point with ‘==’ or ‘!=’ is unsafe" | none |
| Output at `-O0` and `-O2` | `nan == nan: 0`, `nan < 1.0: 0, nan > 1.0: 0`, `size = 3`, then `1 -> 99`, `2 -> 20`, `3 -> 30` | same |
