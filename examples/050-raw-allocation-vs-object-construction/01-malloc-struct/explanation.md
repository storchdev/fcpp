# 050 — Raw allocation vs. object construction

## Why the bad code is wrong (`bad.cpp`)

`std::malloc(sizeof(Config))` returns storage, not a `Config`. The default member initializers (`int retries = 3;`) are applied by a constructor, and no constructor ran. Casting the pointer to `Config*` and reading `c->retries` therefore reads storage that holds no object and has no defined value. (For implicit-lifetime types such as an aggregate, C++20 can implicitly create objects in `malloc` storage, but the *value* is still indeterminate; the initializers do not run.) The pattern appears when C-style allocation is mixed into C++, often through an allocator or a pool.

MemorySanitizer reports `WARNING: MemorySanitizer: use-of-uninitialized-value` at the comparison on `bad.cpp` line 18 (clang++ 23.1.1, `-O0` and `-O1`, `-std=c++17`). AddressSanitizer would not: the memory is allocated and in bounds, it is only uninitialized. clang-tidy's analyzer reported `clang-analyzer-core.UndefinedBinaryOperatorResult` (`The left operand of '==' is a garbage value`) only when run with a broad set of checks (`performance-*,bugprone-*,clang-analyzer-*,…`); with that single check enabled it printed nothing, so I do not list it as a detection. No `-Wall -Wextra` warning from either compiler.

## The fix (`good.cpp`)

Construct the object: `std::make_unique<Config>()` or `new Config`. If raw storage is needed (an allocator, a pool), construct in it with placement new or `std::construct_at` and destroy it before releasing the memory.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
