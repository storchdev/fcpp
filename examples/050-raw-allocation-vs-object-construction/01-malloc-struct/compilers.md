# 050 — Raw allocation vs. object construction: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=memory`, `-O0` and `-O2`).** Neither compiler warns, and neither build prints anything at `-O0` or `-O2` (the `default retries` branch is not taken in my runs). MemorySanitizer is only available with clang++, where it reports `use-of-uninitialized-value` at `-O0`, `-O1` and `-O2`; g++ rejects `-fsanitize=memory` (`unrecognized argument`). That is why the checker builds this case with clang++.
