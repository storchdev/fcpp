# 078.02 — RTTI during construction or destruction: a base that is not constructed yet: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=undefined`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | `-O0`: none; `-O2`: `-Wuninitialized` ("‘w.Widget::<unnamed>.Observer::_vptr.Observer’ is used uninitialized") | none |
| Plain run, `-O0` and `-O2` | crashes (core dumped; exit status 139 at `-O0`) | prints `registering 6Widget`, exit status 0 |
| UBSan, `-O0`, `-O1`, `-O2` | `load of null pointer of type '<unknown> *'` and `applying non-zero offset 18446744073709551608 to null pointer` | no report |
