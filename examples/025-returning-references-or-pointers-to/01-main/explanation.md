# 025 — Returning references or pointers to local objects

## Why the bad code is wrong (`bad.cpp`)

A reference or raw pointer is just an address with a type; it does not own or extend the lifetime of what it names. `make_greeting` builds a local `std::string s`, then returns a `const std::string&` to it. When the function returns, `s` is destroyed (its heap buffer is freed, its storage is released), so the returned reference refers to an object whose lifetime has ended. Using it is undefined behavior.

`make_tag` is the same bug one level down: `c_str()` returns a pointer into the string's internal buffer, and that buffer goes away with `t`. Nothing here "looks" wrong at the call site; `const char*` and `const std::string&` are perfectly normal return types.

Why it often appears to work: the freed stack/heap bytes usually still contain the old characters for a while, so the program prints `hello, world` anyway. The failure shows up later — after an unrelated change reuses that stack slot, under optimization, or when the allocator reuses the freed heap block. The compilers differ here (see `compilers.md`): g++ warns about the returned reference but not about the `c_str()` pointer, while clang++ warns about both.

Notably, binding a returned reference to `const std::string& g` does **not** extend the lifetime: lifetime extension only applies to temporaries bound directly, and here the function returned a reference to a non-temporary that is already dead.

AddressSanitizer is what the checker uses, with `detect_stack_use_after_return=1`; what it reports differs by compiler (see `compilers.md`).

## The fix (`good.cpp`)

Return by value. Copy elision (guaranteed for prvalues since C++17) and move semantics make this cheap; you don't pay for an extra copy. Only return a reference when it names something that outlives the call (a member, a static, or an argument).

## Rust (`good.rs`)

The borrow checker rejects the bad version at compile time (E0515: cannot return reference to local variable). Returning an owned `String` is the idiomatic equivalent.
