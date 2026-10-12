# 159.01 — `std::any` and `std::variant` runtime type assumptions: variant `get`

## Why the bad code is wrong (`bad.cpp`)

`std::get<T>(v)` on a `std::variant` that currently holds another alternative throws `std::bad_variant_access`. It is well-defined, but the program must handle it. The program printed `bad_variant_access: std::get: wrong index for variant` with both compilers at `-O0` and `-O2`. Nothing warns at compile time; neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use `std::get_if<T>(&v)` (a null pointer on mismatch), `std::holds_alternative<T>(v)`, or `std::visit`. The fixed program prints `not a string, index = 0`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

