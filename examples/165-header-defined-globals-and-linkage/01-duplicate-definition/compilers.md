# 165.01 — Header-defined globals and linkage: duplicate definition: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Link | fails: ``multiple definition of `counter'`` | fails: ``multiple definition of `counter'`` |
| Wrapper line | differs (see `explanation.md`) | differs (see `explanation.md`) |
