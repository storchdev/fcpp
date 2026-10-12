# 050 — Raw allocation vs. object construction: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=memory`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | nothing (the `default retries` branch is not taken in my runs) | nothing (same) |
| MemorySanitizer, `-O0`, `-O1`, `-O2` | rejects `-fsanitize=memory` (`unrecognized argument`) | `use-of-uninitialized-value` |
