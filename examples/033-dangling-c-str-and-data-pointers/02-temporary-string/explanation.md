# 033.02 — Dangling `c_str()` and `data()` pointers: temporary string

## Why the bad code is wrong (`bad.cpp`)

`config_path()` returns a `std::string` by value: a prvalue that is materialized as a temporary. `.c_str()` returns a pointer into that temporary's buffer, and the temporary is destroyed at the end of the full-expression, the semicolon on that line. `p` therefore points at freed memory when `printf` reads it: undefined behavior. AddressSanitizer reports `heap-use-after-free` on g++ 16.2.1 and clang++ 23.1.1 (`-std=c++17 -O1`).

Using the pointer *within* the same full-expression is fine: `std::printf("%s\n", config_path().c_str());` is the second use in `good.cpp`. Only storing the pointer past the semicolon is wrong, which is why the pattern looks so familiar.

Detection: clang++ warns under `-Wall -Wextra`: `warning: object backing the pointer will be destroyed at the end of the full-expression [-Wdangling-gsl]`; clang-tidy `clang-analyzer-cplusplus.InnerPointer` reports `Inner pointer of container used after re/deallocation`. g++ 16.2.1 did not warn on `bad.cpp`.

## The fix (`good.cpp`)

Name the string (`const std::string path = config_path();`) so it outlives the pointer, or consume the pointer in the same full-expression.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
