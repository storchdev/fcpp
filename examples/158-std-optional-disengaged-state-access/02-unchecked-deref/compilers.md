# 158.02 — `std::optional` disengaged-state access: unchecked dereference: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** The runtime behavior and warnings differ.

| | g++ | clang++ |
| --- | --- | --- |
| Warnings `-O0` | none | none |
| Warnings `-O2` | `‘%s’ directive argument is null [-Wformat-overflow=]` | none |
| Plain run `-O0` | assertion `this->_M_is_engaged()` failed, aborts | same assertion, aborts |
| Plain run `-O2` | `user = (null)` | `user = ` followed by garbage bytes |

