# 116.02 — Implicit conversion ranking: literal to bool

## Why the bad code is wrong (`bad.cpp`)

A string literal is a `const char[6]`; converting it to `bool` (array-to-pointer, then pointer-to-bool) is a standard conversion sequence, and converting it to `std::string` needs a user-defined conversion (the converting constructor). A standard conversion sequence always ranks better than a user-defined one, so `put(bool)` is selected. The program printed `put(bool)` with both compilers at `-O0` and `-O2`.

The conversion to `bool` is silent in this overload set. Neither compiler warns under `-Wall -Wextra`, and no tool I ran reported it.

## The fix (`good.cpp`)

Pass a `std::string` (`"hello"s`), add a `const char*` overload, or remove the `bool` overload. The fixed program prints `put(string)`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

