# 158.02 — `std::optional` disengaged-state access: unchecked dereference

## Why the bad code is wrong (`bad.cpp`)

`operator*` and `operator->` on an `optional` that does not contain a value are undefined behavior; `value()` instead throws `std::bad_optional_access`. In this build the behavior differs by optimization level: at `-O0` both compilers abort with the libstdc++ assertion `this->_M_is_engaged()` failed (the build has library assertions enabled), while g++ at `-O2` printed `user = (null)`.

Plain `-O2` runs printed `user = (null)` (g++) and garbage bytes (clang++), exit status 0. The check that catches it statically is clang-tidy (run on the source, independent of the compiler): `bugprone-unchecked-optional-access` reports `unchecked access to optional value`. g++ at `-O2` also warns `‘%s’ directive argument is null [-Wformat-overflow=]` (a consequence, not a detection of the optional misuse). Neither compiler warns at `-O0` under `-Wall -Wextra`.

## The fix (`good.cpp`)

Check before access (`if (user)`) or use `value()` / `value_or()` when an exception or default is the right behavior. The fixed program prints `user = (none)`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

