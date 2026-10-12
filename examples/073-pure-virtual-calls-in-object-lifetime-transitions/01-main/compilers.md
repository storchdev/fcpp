# 073 — Pure virtual calls in object lifetime transitions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both programs print `pure virtual method called` and `terminate called without an active exception`, then dump core, at `-O0` and `-O2`. `Derived::run` is never reached. `clang-tidy` (`clang-analyzer-cplusplus.PureVirtualCall`) reports the call statically.
