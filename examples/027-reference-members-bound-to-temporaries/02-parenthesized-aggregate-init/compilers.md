# 027.02 — Reference members bound to temporaries: parenthesized aggregate initialization: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none at `-O0`; at `-O2` `-Wdangling-pointer=` and `-Wuninitialized` | `-Wdangling` at `-O0` and `-O2` (`temporary whose address is used as value of local variable 'parens' will be destroyed at the end of the full-expression`) |
| No sanitizer | long string, then garbage at `-O0` and an empty line at `-O2` | long string, then garbage |
| ASan `-O0`, `-O1` | `stack-use-after-scope` | `stack-use-after-scope` |
| ASan `-O2` | `stack-use-after-scope` | no report in my run |

So at `-O2` this case is caught by ASan with g++ but not with clang++, which is another reason the checker's sanitizer builds use g++ (except for MemorySanitizer).
