# 152 — Borrowed ranges vs. owning ranges: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Result, `-O0` and `-O2` | `bad.cpp` rejected | `bad.cpp` rejected |
| Diagnostic wording | differs; quoted in `explanation.md` | differs; quoted in `explanation.md` |
