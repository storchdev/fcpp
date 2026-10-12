# 163 — Function-local static initialization

## Why the bad code is wrong (`bad.cpp`)

Function-local statics are initialized the first time control passes through the declaration, and since C++11 that initialization is thread-safe. The standard also says that if control re-enters the declaration recursively while the variable is being initialized, the behavior is undefined. Here the initializer of `v` calls `f(n - 1)`, which reaches the same declaration again while the first initialization is still in progress. With both compilers (linking libstdc++), the program printed `terminate called after throwing an instance of '__gnu_cxx::recursive_init_error'` and dumped core at `-O0` and `-O2`: that is what this implementation does, not something the standard guarantees.

Neither compiler warns under `-Wall -Wextra`. It is easy to write when the initializer calls a helper that eventually calls the enclosing function.

## The fix (`good.cpp`)

Break the cycle: do the recursive work before reaching the static's declaration, or initialize the static from something that cannot call back into the function. The fixed program prints `1` with both compilers.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

