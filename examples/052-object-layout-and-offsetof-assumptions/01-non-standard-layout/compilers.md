# 052 — Object layout and `offsetof` assumptions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Output, `-O0` and `-O2` | `4` and `8` | `4` and `8` |
| `-Winvalid-offsetof`, `Derived` (line 17) | `'offsetof' within non-standard-layout type 'Derived' is conditionally-supported` | `'offsetof' on non-standard-layout type 'Derived'` |
| `-Winvalid-offsetof`, `Poly` (line 18) | same warning, for `Poly` | same warning, for `Poly` |
| Unrelated extra warning | none | `-Wunused-private-field`: `private field 'priv' is not used` |
