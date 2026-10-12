# 175 — `memcpy` vs. element-wise copying

## Why the bad code is wrong (`bad.cpp`)

`memcpy` copies bytes. It is only meaningful for trivially copyable types: for those, copying the bytes creates a valid object (and `std::copy` is allowed to use `memmove` itself). `std::string` is not trivially copyable: a bitwise copy duplicates the pointer to its heap buffer without creating a new owner, and destroying both objects frees the same buffer twice (undefined behavior; the 80-character string is beyond the small-string buffer so it is on the heap). Plain runs printed `free(): double free detected in tcache 2` and dumped core with both compilers at `-O0` and `-O2`.

AddressSanitizer reports `attempting double-free` at `-O0`, `-O1` and `-O2` with both compilers. Neither compiler warns under `-Wall -Wextra` (`-Wclass-memaccess` is not triggered, because the destination is a raw byte array).

## The fix (`good.cpp`)

Use `std::copy` / copy construction, which does the right thing per type and is also free to use `memmove` when the type is trivially copyable (the fixed program asserts `!is_trivially_copyable_v<std::string>` and `is_trivially_copyable_v<int>`). The fixed program prints `dst[0].size = 80, b[2] = 3`.

## Rust (no `good.rs`)

Rust's `Copy` types are bitwise-copyable, and `String` is `Clone` only: the type system makes the same split. No Rust equivalent is provided for this case.

