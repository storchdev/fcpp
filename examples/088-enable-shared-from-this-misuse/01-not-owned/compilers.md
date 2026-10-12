# 088.01 — `enable_shared_from_this` misuse: object not owned by a `shared_ptr`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Run, `-O0` and `-O2` | `terminate called after throwing an instance of 'std::bad_weak_ptr'` (`what():  bad_weak_ptr`), core dumped | `terminate called after throwing an instance of 'std::bad_weak_ptr'` (`what():  bad_weak_ptr`), core dumped |
