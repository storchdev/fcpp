# 103 — `std::remove` vs. container erasure: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** Both warn with `-Wunused-result` at `-O0` and `-O2` (it is on by default in this libstdc++), with different wording (see below), and both print `size = 4: 1 3 3 2`.

| | g++ | clang++ |
| --- | --- | --- |
| Warning | "ignoring return value of ‘_FIter std::remove(_FIter, _FIter, const _Tp&) [with ...]’, declared with attribute ‘nodiscard’ [-Wunused-result]" | "ignoring return value of function declared with 'nodiscard' attribute [-Wunused-result]" |
