# 126.02 — `std::optional::value()` and `std::expected::value()`: `expected::value()` throws

## Why the bad code is wrong (`bad.cpp`)

`std::expected<T, E>::value()` returns the value if present and otherwise throws `std::bad_expected_access<E>`. An `expected` is introduced to avoid exceptions, so calling `value()` on it quietly re-introduces one. With no handler, the exception reaches `std::terminate`: the program printed `terminate called after throwing an instance of 'std::bad_expected_access<std::__cxx11::basic_string<...>>'` with `what(): bad access to std::expected without expected value` and dumped core, with both compilers at `-O0` and `-O2`.

Neither compiler warns under `-Wall -Wextra`, and no tool I ran reported it. `std::expected` requires C++23 (the build uses `-std=c++23`).

## The fix (`good.cpp`)

Check `has_value()`/`operator bool` and read `error()`, or use `value_or`. The fixed program prints `error: empty input`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

