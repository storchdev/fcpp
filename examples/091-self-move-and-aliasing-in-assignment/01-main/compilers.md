# 091 — Self-move and aliasing in assignment: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns on `bad.cpp` (the self-move is hidden behind `assign`), and both print `Buffer: data is null` and `vector: size=0` at `-O0` and `-O2`. In a separate scratch test, `v = std::move(v);` written directly gave `-Wself-move` in both compilers. `clang-tidy` with `bugprone-unhandled-self-assignment` and `cert-oop54-cpp` reported nothing.
