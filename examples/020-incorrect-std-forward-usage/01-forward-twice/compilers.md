# 020.01 — Incorrect `std::forward` usage: forwarding twice: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `store: "a-long-enough-string-to-defeat-sso-0123456789"` and `audit: ""` at `-O0` and `-O2`.
