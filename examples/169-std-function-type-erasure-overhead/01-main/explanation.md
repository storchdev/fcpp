# 169 — `std::function` type-erasure overhead

## Why the bad code is wrong (`bad.cpp`)

`std::function` stores its callable in small internal storage when it fits and otherwise on the heap. The lambda captures a 32-byte struct, more than libstdc++'s `std::function` can hold inline (`sizeof(std::function<long()>)` is 32 here), so each conversion at the call site allocates, and each call goes through an indirect call. The counting `operator new` printed `allocations = 1000, sum = 5000, sizeof(std::function) = 32` with both compilers at `-O0` and `-O2`: one allocation per iteration. The size of the small buffer is implementation-defined; I only observed libstdc++.

Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Take the callable as a template parameter (as in `good.cpp`) so its type is preserved and the call can be inlined; use `std::function` only where erasure is needed (stored callbacks, runtime-chosen callables). The fixed program printed `allocations = 0`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

