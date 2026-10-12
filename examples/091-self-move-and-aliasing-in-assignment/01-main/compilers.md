# 091 — Self-move and aliasing in assignment: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings (self-move hidden behind `assign`) | none | none |
| Output, `-O0` and `-O2` | `Buffer: data is null` and `vector: size=0` | `Buffer: data is null` and `vector: size=0` |
| Scratch test: `v = std::move(v);` written directly | `-Wself-move` | `-Wself-move` |
| `clang-tidy` `bugprone-unhandled-self-assignment`, `cert-oop54-cpp` | reported nothing | reported nothing |
