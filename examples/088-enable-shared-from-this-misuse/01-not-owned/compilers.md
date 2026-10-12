# 088.01 — `enable_shared_from_this` misuse: object not owned by a `shared_ptr`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both terminate with `terminate called after throwing an instance of 'std::bad_weak_ptr'` (`what():  bad_weak_ptr`) and dump core at `-O0` and `-O2`.
