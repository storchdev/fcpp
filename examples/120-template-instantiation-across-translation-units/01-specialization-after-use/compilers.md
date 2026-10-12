# 120.01 — Template instantiation across translation units: specialization after use: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** Both reject `bad.cpp` at `-O0` and `-O2`; see the table.

| | g++ | clang++ |
| --- | --- | --- |
| Error | "specialization of ‘Name<int>’ after instantiation" (followed by "redefinition of ‘struct Name<int>’") | "explicit specialization of 'Name<int>' after instantiation" |

