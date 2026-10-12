# 014.01 — `auto` with brace initialization: copy-list gives `initializer_list`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `sizeof(a)=16 sizeof(b)=4, a.size()=1` | `sizeof(a)=16 sizeof(b)=4, a.size()=1` |
