# 019.02 — Forwarding references vs. rvalue references: not every `&&` forwards: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Result, `-O0` and `-O2` | rejects `consume(names)` at line 13, one error | rejects `consume(names)` at line 13, one error |
| Error text | `cannot bind rvalue reference of type 'std::vector<std::string>&&' to lvalue of type 'std::vector<std::string>'` | `no matching function for call to 'consume'` |
