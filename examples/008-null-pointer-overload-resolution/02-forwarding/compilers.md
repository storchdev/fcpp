# 008.02 — Null pointer overload resolution: forwarding loses the null pointer constant: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** Both reject `std::make_unique<Node>(0)`, with different text, both pointing into `<bits/unique_ptr.h>` line 1105. g++: `invalid conversion from 'int' to 'Node*' [-fpermissive]`. clang++: `no matching constructor for initialization of 'Node'`. The result is the same at `-O0` and `-O2`.
