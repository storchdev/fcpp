# 008.02 — Null pointer overload resolution: forwarding loses the null pointer constant: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Result, `-O0` and `-O2` | rejects `std::make_unique<Node>(0)` | rejects `std::make_unique<Node>(0)` |
| Error location | `<bits/unique_ptr.h>` line 1105 | `<bits/unique_ptr.h>` line 1105 |
| Error text | `invalid conversion from 'int' to 'Node*' [-fpermissive]` | `no matching constructor for initialization of 'Node'` |
