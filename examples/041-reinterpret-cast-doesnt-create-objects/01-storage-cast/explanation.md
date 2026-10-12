# 041 — `reinterpret_cast` doesn't create objects

## Why the bad code is wrong (`bad.cpp`)

`reinterpret_cast<Widget*>(storage)` converts a pointer value; it does not run a constructor, so no `Widget` exists in `storage`. `w->get()` is a member call on a pointer that does not point to an object of type `Widget`: undefined behavior. For a polymorphic type the damage is concrete: the vtable pointer is set by the constructor, and the buffer holds zeros, so a virtual call goes through a null vptr.

Observed (`-std=c++17 -O1 -fsanitize=undefined`): g++ 16.2.1 reports `runtime error: member call on address 0x… which does not point to an object of type 'Widget'` with `note: object has invalid vptr`. clang++ 23.1.1 reports nothing and crashes: `UndefinedBehaviorSanitizer: SEGV on unknown address 0x000000000001 (pc 0x000000000001 …)` (the call jumped through the bad vtable pointer). `Widget` has virtual functions, so it is not an implicit-lifetime type: I confirmed `static_assert(!std::is_implicit_lifetime_v<Widget>)` and `static_assert(std::is_implicit_lifetime_v<Plain>)` for an aggregate `Plain` on both compilers with `-std=c++23`. For implicit-lifetime types the C++20 object model can create objects implicitly in suitable storage; `Widget`, with virtual functions, is not.

clang-tidy `cppcoreguidelines-pro-type-reinterpret-cast` reports the cast, as it does for any `reinterpret_cast`. No `-Wall -Wextra` warning from either compiler.

## The fix (`good.cpp`)

Create the object with placement new, use the pointer it returns, and call the destructor when done. `std::construct_at` (C++20) does the same. The aligned buffer provides storage only.

## Rust (no `good.rs`)

Safe Rust cannot reinterpret a byte buffer as a struct; `MaybeUninit<T>` plus an explicit `write` is the unsafe analogue.
