# 122 — `noexcept` violations

## Why the bad code is wrong (`bad.cpp`)

An exception that tries to leave a `noexcept` function calls `std::terminate`; it does not propagate, and the stack may not be unwound first. `parse(-1)` throws, the function promised not to, and the `catch` in `main` is never reached. The output was `terminate called after throwing an instance of 'std::invalid_argument'` / `what(): negative` and a core dump with both compilers at `-O0` and `-O2`.

Both compilers warn without extra flags (the throw is directly visible in the function): g++ "‘throw’ will always call ‘terminate’ [-Wterminate]", clang++ "'parse' has a non-throwing exception specification but can still throw [-Wexceptions]". The warning only sees direct throws: a `noexcept` function that calls something that throws is not diagnosed here (I did not test that). `clang-tidy bugprone-exception-escape` reports this one.

## The fix (`good.cpp`)

Remove `noexcept` from functions that can throw, or handle the error inside (return a status, or catch). The fixed program prints `caught: negative`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

