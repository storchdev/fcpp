# 073 — Pure virtual calls in object lifetime transitions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Run, `-O0` and `-O2` | prints `pure virtual method called` and `terminate called without an active exception`, then dumps core; `Derived::run` is never reached | same |
| `clang-tidy` `clang-analyzer-cplusplus.PureVirtualCall` | reports the call statically | reports the call statically |
