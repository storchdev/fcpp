# 083.01 — Copy elision vs. actual moves: named local: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** Both reject `bad.cpp` at `-O0` and `-O2`:

| | g++ | clang++ |
| --- | --- | --- |
| Error | "use of deleted function ‘Pinned::Pinned(Pinned&&)’" | "call to deleted constructor of 'Pinned'" |
