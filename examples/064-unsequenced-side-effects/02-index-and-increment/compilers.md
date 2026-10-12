# 064.02 — Unsequenced side effects: `a[i] = i++` before C++17: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++14 -Wall -Wextra`, `-O0` and `-O2`; also `-std=c++17`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings, `-std=c++14` | `-Wsequence-point`: "operation on ‘i’ may be undefined" (reported twice) | `-Wunsequenced`: "unsequenced modification and access to 'i'" |
| Warnings, `-std=c++17` | one `-Wsequence-point` | none |
| Output at `-O0` and `-O2`, both standards | `a[0]=0 a[1]=10 i=1` | `a[0]=0 a[1]=10 i=1` |
