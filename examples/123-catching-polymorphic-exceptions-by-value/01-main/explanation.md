# 123 — Catching polymorphic exceptions by value

## Why the bad code is wrong (`bad.cpp`)

`catch (std::exception e)` copy-initializes `e` from the thrown object as a `std::exception`, so the `DiskError` part is sliced off and `e.what()` calls `std::exception::what`. The program printed `what() = std::exception` with both compilers at `-O0` and `-O2`, instead of `disk full`. Nothing is undefined; the message is simply lost, and a catch by value of a type with a copy that can throw adds a second failure path.

g++ warns under `-Wall`: "catching polymorphic type ‘class std::exception’ by value [-Wcatch-value=]". clang++ gave no warning with `-Wall -Wextra`.

## The fix (`good.cpp`)

Catch by (const) reference: `catch (const std::exception& e)`. The fixed program prints `what() = disk full`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

