# 166 — ABI incompatibility: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings, each file compiled | none | none |
| Link | fails: ``undefined reference to `greeting[abi:cxx11]()'`` | fails: ``undefined reference to `greeting[abi:cxx11]()'`` |
