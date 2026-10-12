# 006.02 — Implicit conversion chains: at most one user-defined conversion: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`).**

| | g++ | clang++ |
| --- | --- | --- |
| Result | rejected | rejected |
| Errors | `could not convert '5.0e+0' from 'double' to 'Distance'`, then `no matching function for call to 'travel'` | `no matching function for call to 'travel'` (one error), with the note `candidate function not viable: no known conversion from 'double' to 'Distance' for 1st argument` |
