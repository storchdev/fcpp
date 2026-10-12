# 045 — Pointer provenance and lifetime

## Why the bad code is wrong (`bad.cpp`)

After `std::free(p)`, `p` holds an *invalid pointer value*; cppreference's pointer page lists "an invalid pointer value" as one of the possible values of a pointer, and notes that two pointers representing the same address may nonetheless have different values. A later `malloc` may return the same address, so `p == q` can be true, but `q` is a pointer to a new object and `p` is not: equal addresses do not make `p` valid. Writing through `p` is undefined behavior, and the compiler is entitled to reason that a write through a pointer derived from the freed allocation cannot affect the new one.

The compilers do exactly different things (`bad.cpp`, `-std=c++17`, no sanitizer; output of the program):

| Compiler | `-O0` | `-O1` | `-O2` |
| --- | --- | --- | --- |
| g++ 16.2.1 | `same address: *q=3` | `same address: *q=2` | `same address: *q=2` |
| clang++ 23.1.1 | `same address: *q=3` | `different` | `different` |

At `-O0` the write through `p` lands in `*q`. With optimization g++ still takes the "same address" branch but then reads `*q` as `2`, as though `*p = 3` could not have changed it; clang++ folds the comparison itself to false. A program whose output depends on the optimization level is the typical symptom.

g++ warns under `-Wall -Wextra`: `warning: pointer ‘p’ may be used after ‘void free(void*)’ [-Wuse-after-free=]`. I could not list this as a verified detection because the checker passes the flag text verbatim and `-Wuse-after-free=` is not accepted without a level (`g++: error: missing argument to ‘-Wuse-after-free=’`), so `detection` is `none`. clang++ gave no warning.

## The fix (`good.cpp`)

Never use a pointer after the storage it pointed to is released; clear it (`p = nullptr`) and use the pointer that names the live object. Do not compare a stale pointer to a new one to decide whether they are "the same object"; keep an explicit handle (index, ID, smart pointer) instead.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
