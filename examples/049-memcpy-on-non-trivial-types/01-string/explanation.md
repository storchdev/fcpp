# 049 — `memcpy` on non-trivial types

## Why the bad code is wrong (`bad.cpp`)

`std::memcpy` copies bytes. cppreference's TriviallyCopyable page guarantees that copying an object's underlying bytes into another object (with `memcpy` or `memmove`) gives that object the same value, for trivially copyable types; nothing guarantees it for other types. `std::string` is not trivially copyable (`good.cpp` checks that with `static_assert`), because it owns a heap buffer and its copy operations allocate. After `std::memcpy(&b, &a, sizeof a)`, `b` holds `a`'s pointer to the same heap buffer: two objects believe they own it. `b.c_str()` appears to work. At the end of `main` both destructors free the same buffer, and the second `delete` of one buffer is undefined behavior; AddressSanitizer reports `attempting double-free` (g++ 16.2.1 and clang++ 23.1.1, `-std=c++17 -O1`). Also, `b`'s own previous state was overwritten without destruction.

Diagnostics, all verified on `bad.cpp`: g++ warns under `-Wall -Wextra`: `warning: ‘void* memcpy(void*, const void*, size_t)’ writing to an object of type ‘std::string’ … with no trivial copy-assignment; use copy-assignment or copy-initialization instead [-Wclass-memaccess]`; clang++ 23.1.1: `warning: first argument in call to 'memcpy' is a pointer to non-trivially copyable type 'std::string' (aka 'basic_string<char>') [-Wnontrivial-memcall]`; clang-tidy `bugprone-undefined-memory-manipulation` reports `undefined behavior, destination object type 'std::string' (aka 'basic_string<char>') is not TriviallyCopyable` (and the same for the source).

## The fix (`good.cpp`)

Use copy construction or assignment (`std::string b = a;`), which duplicate ownership correctly. For arrays of such objects use `std::copy`/`std::uninitialized_copy`. `memcpy` remains right for trivially copyable types.

## Rust (`good.rs`)

A Rust move is also a bitwise copy, but the source is then treated as moved-from and is never dropped, so ownership stays unique. Duplicating requires an explicit `.clone()`.
