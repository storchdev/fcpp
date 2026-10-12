# 071 — Deleting through a non-virtual base destructor: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | `-Wdelete-non-virtual-dtor` | `-Wdelete-non-abstract-non-virtual-dtor`: "delete called on non-final 'Base' that has virtual functions but non-virtual destructor" |
| Plain run, `-O0` and `-O2` | prints `~Base` | prints `~Base` |
| ASan `-O0`, `-O1`, `-O2` | `new-delete-type-mismatch` | `new-delete-type-mismatch` (its `SUMMARY` line names a binary offset instead of the source line) |
| With `ASAN_OPTIONS=new_delete_type_mismatch=0` | `101 byte(s) leaked in 1 allocation(s)` | same |
