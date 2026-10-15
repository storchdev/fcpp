# 190 — Overloaded address-of operator

## Why the bad code is wrong (`bad.cpp`)

For a class object, unary `&` can call an overloaded `operator&` instead of the built-in address-of operation. `Handle::operator&` returns `nullptr`, so `&handle == nullptr` prints `true` even though `handle` is a live local object.

Generic code that assumes `&value` is a real object address can therefore store or pass a misleading pointer. This example is well defined, and neither compiler warned under the tested flags. Reviewers should inspect whether the type overloads unary `&` when code needs a physical object address.

## The fix (`good.cpp`)

Use `std::addressof(handle)` when the actual object address is required. It obtains that address even when the type overloads `operator&`; the example dereferences it to print the object's `id`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this C++ operator-overloading case.
