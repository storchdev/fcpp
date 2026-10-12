# 019.02 — Forwarding references vs. rvalue references: not every `&&` forwards: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** Both reject `consume(names)` at line 13 with one error, at both levels. g++: `cannot bind rvalue reference of type 'std::vector<std::string>&&' to lvalue of type 'std::vector<std::string>'`. clang++: `no matching function for call to 'consume'`.
