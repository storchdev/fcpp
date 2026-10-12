# 048 — `std::launder` and pointer reuse

## Why the bad code is wrong (`bad.cpp`)

`new (buf) Item{42};` creates an `Item` in `buf`, but the expression's value is discarded, and `p` is made with `reinterpret_cast<Item*>(buf)`. That conversion yields a pointer that still points at the `unsigned char` array, not at the `Item`, so `p->v` accesses an object through a pointer that does not point to it: undefined behavior. cppreference's `std::launder` notes name this as a typical use: "obtaining a pointer to an object created by placement new from a pointer to an object providing storage for that object", and the lifetime page says that when an object is not "transparently replaceable" by another, a valid pointer to the new object may be obtained with `std::launder`.

I could not make this fail: `bad.cpp` printed `42` with g++ 16.2.1 and clang++ 23.1.1 at `-O0`, `-O1` and `-O2` (`-std=c++17`). It is undefined behavior that currently works, so the compilers may later exploit it, and the program is still wrong. There is no sanitizer for this rule; `detection` lists only clang-tidy `cppcoreguidelines-pro-type-reinterpret-cast`, which flags every `reinterpret_cast` and does not know about `launder`. Review rule: a `reinterpret_cast` from a buffer to the type constructed in it, without using the pointer returned by placement new, needs a `launder`.

## The fix (`good.cpp`)

Keep the pointer returned by placement new (`Item* made = new (buf) Item{42};`). When the original pointer cannot be kept (for example an object replaced inside a container whose old pointers must remain usable, or storage accessed later through the buffer), use `std::launder(reinterpret_cast<Item*>(buf))`, as `good.cpp` also shows. `launder` has no effect on the pointer value; it only tells the compiler the pointer's provenance: always use its return value, and only when an object of that type really exists at that address.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
