# 040 — Strict aliasing violations

## Why the bad code is wrong (`bad.cpp`)

An object may be accessed only through a glvalue of its own type (or a few related types such as a signed/unsigned variant, a base class, or `char`/`unsigned char`/`std::byte`). Here a single `int` object is written through `int*` and then through `float*`; the `float` store is not a valid access to an `int`, so the program has undefined behavior. The optimizer is allowed to use that rule: `*f = 2.0f` cannot modify an `int`, so `return *i` may return the value just stored (1).

Observed output of `bad.cpp` (`-std=c++17`, g++ 16.2.1 and clang++ 23.1.1):

| Compiler | `-O0` | `-O1` | `-O2` |
| --- | --- | --- | --- |
| g++ | `r=1073741824` | `r=1073741824` | `r=1` |
| clang++ | `r=1073741824` | `r=1` | `r=1` |

`x` is `1073741824` (the bit pattern of `2.0f`) in every row; only the value returned from `set_and_read` changes. So the program's result depends on the optimization level, which is the signature of this bug. Compiling with `-O2 -fno-strict-aliasing` made both compilers print `r=1073741824` (verified), but that flag only hides the bug in code you control.

Detection is poor: `-Wstrict-aliasing` at `-O2` produced no warning on either compiler for this code, and none of the sanitizers I used (address, undefined, thread, memory) checks the aliasing rules. clang-tidy `cppcoreguidelines-pro-type-reinterpret-cast` flags the cast, but it flags every `reinterpret_cast`, justified or not.

## The fix (`good.cpp`)

`std::bit_cast<std::uint32_t>(f)` (C++20) copies the object representation into a new object of the other type; `std::memcpy` into an `unsigned` object does the same before C++20, and compiles to the same load. Do not use unions for this (entry 046).

## Rust (no `good.rs`)

Safe Rust has no such pointer cast; `f32::to_bits` is shown under entry 046.
