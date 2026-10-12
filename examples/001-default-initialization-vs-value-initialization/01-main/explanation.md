# 001 — Default initialization vs. value initialization

## Why the bad code is wrong (`bad.cpp`)

C++ has several initialization forms that differ by a single character but have very different meanings:

| Syntax | Kind | `int` / aggregate of `int` |
| --- | --- | --- |
| `T x;` | default-initialization | **indeterminate** (for non-class types with automatic/dynamic storage) |
| `T x{};` / `T x = T();` | value-initialization | zero-initialized |
| `new T` | default-initialization | indeterminate |
| `new T()` / `new T{}` | value-initialization | zero-initialized |

`Point` has no constructor and no default member initializers, so it is an aggregate whose `int` members have no inherent value. `Point p;` leaves `p.x` and `p.y` holding whatever bytes were on the stack. `Point q{};` zero-initializes them. Both lines look like "make a Point" and a reader skimming the code can't tell they differ.

Reading an indeterminate value of type `int` is undefined behavior (not merely "an arbitrary number"). In practice the compiler is free to treat the value as *different* each time it's observed, delete the read, or fold a later branch on it as always-true and always-false at once. So the program may print garbage, print zeros in a debug build and garbage in release, or behave differently after unrelated code changes. Note: the exceptions are `unsigned char`/`std::byte` copies, and in C++26 reading becomes "erroneous behavior" with a defined (but still wrong) value, which reduces but doesn't eliminate the bug.

The `new int[4]` line is the same trap hidden behind a smart pointer: `std::unique_ptr<int[]>(new int[4])` default-initializes the array. Sanitizers: this is detectable by MemorySanitizer (clang) but **not** by AddressSanitizer, because the memory is perfectly valid — just unwritten.

## The fix (`good.cpp`)

- Give members default member initializers (`int x{};`) so every construction path is safe.
- Prefer `T x{};` for locals you want zeroed.
- `std::make_unique<T[]>(n)` value-initializes; if you deliberately want uninitialized storage, use `std::make_unique_for_overwrite<T[]>(n)` (C++20) so the intent is visible, and write before you read.

## Rust (`good.rs`)

Safe Rust requires definite initialization: using an unassigned binding is a compile error (E0381), and struct literals must name every field. Zeroed defaults are explicit via `Default`. The only way to get uninitialized memory is `MaybeUninit`, which is `unsafe` to read.
