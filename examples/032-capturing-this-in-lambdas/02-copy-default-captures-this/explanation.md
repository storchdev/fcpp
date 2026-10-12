# 032.02 — Capturing `this` in lambdas: `[=]` does not copy members

## Why the bad code is wrong (`bad.cpp`)

`[=]` means "capture by copy every *automatic variable* the body uses". A data member is not an automatic variable: the body's `n` means `this->n`, so the closure captures the `this` pointer by copy and reads the live member later. The snapshot is therefore not a snapshot. After `c.n = 99;`, `snap()` returns `99` (g++ 16.2.1 and clang++ 23.1.1, `-std=c++17`), not `1`. This case is defined behavior, `LOGIC`; it becomes case 01 if the object dies.

Under `-std=c++17` neither compiler warns with `-Wall -Wextra`. clang-tidy `cppcoreguidelines-misleading-capture-default-by-value` reports `lambdas that implicitly capture 'this' should not specify a by-value capture default`. In C++20 the compilers also warn (see case 01).

## The fix (`good.cpp`)

Copy the member explicitly: `[n = n] { return n; }` (an init-capture, C++14), which makes the closure independent of the object, or `[*this]` to copy the whole object.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
