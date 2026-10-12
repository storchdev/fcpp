# 037.01 — Destructor and temporary destruction timing: the unnamed lock guard: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=thread`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warning (line 13) | `-Wunused-result` (`ignoring return value of 'std::lock_guard<...>::lock_guard(mutex_type&)' ..., declared with attribute 'nodiscard'`) | `-Wunused-value` (`ignoring temporary created by a constructor declared with 'nodiscard' attribute`) |
| No sanitizer, `-O0` | `counter = 2000` | `counter = 1850` |
| No sanitizer, `-O2` | `counter = 1999` | `counter = 2000` |
| TSan `-O0`, `-O1`, `-O2` | `data race` | `data race` |

Both compilers warn at compile time, but under different flag names. The unsanitized results vary between runs and levels; only TSan is reliable.
