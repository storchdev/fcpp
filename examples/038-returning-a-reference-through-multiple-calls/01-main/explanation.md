# 038 — Returning a reference through multiple calls

## Why the bad code is wrong (`bad.cpp`)

Each function in the chain is individually reasonable: `load_names()` returns a vector by value, `first(v)` returns `v.front()` by reference into its argument, and `default_name()` returns that reference. In `default_name`, `load_names()` creates a temporary vector that lives until the end of the full-expression `return first(load_names());`; the reference returned by `first` points into that vector and is returned from `default_name`, outliving it. By the time `main` calls `c_str()`, the vector and its elements have been destroyed. This is the exception from entry 026: a reference returned from a call is not bound to the temporary, so there is no extension, and returning a reference does not extend anything beyond the function.

AddressSanitizer reports `heap-use-after-free` on g++ 16.2.1 and clang++ 23.1.1 (`-std=c++17 -O1`). In this chain neither compiler warns under `-Wall -Wextra`, and none of the clang-tidy checks I ran flagged it, because each function looks correct in isolation: the dangling object is only visible by following the whole chain. That is how it ends up in code review: every signature that returns `const T&` is a promise about the lifetime of something else.

## The fix (`good.cpp`)

Return by value where ownership is needed (`std::string default_name()`), so the copy is made while the vector is still alive. Generally: a function may return a reference only to something that outlives the call — a member, a static, or an argument the caller still holds.

## Rust (`good.rs`)

`fn first(v: &[String]) -> &String` is tied to its argument by lifetime elision. Returning that reference from a function that owns the vector is `E0515` ("returns a value referencing data owned by the current function"); `good.rs` shows the rejected signature commented out and returns an owned `String` instead.
