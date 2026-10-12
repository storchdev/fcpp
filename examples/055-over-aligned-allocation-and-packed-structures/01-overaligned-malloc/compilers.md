# 055.01 — Over-aligned allocation and packed structures: `malloc` for an over-aligned type: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=undefined`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| No sanitizer | prints an address at both levels | prints an address at both levels |
| UBSan `-O0` | no report | `constructor call on misaligned address ... for type 'Block', which requires 64 byte alignment`, plus a `member access within misaligned address` error |
| UBSan `-O1`, `-O2` | `store to misaligned address ... for type 'struct Block', which requires 64 byte alignment`, plus a `member access within misaligned address` error | same two kinds as at `-O0` |

g++'s UBSan did not report anything at `-O0` in my run, so the sanitizer detection holds for g++ only at `-O1` and above, which is the level the checker uses (`-O1`).
