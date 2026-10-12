# 147 — `std::atomic_ref` lifetime and alignment: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).** No difference in kind: neither compiler warns, and TSan reports `data race` at `-O0`, `-O1` and `-O2` with both (at `-O2` g++'s summary points into libstdc++'s thread code).

