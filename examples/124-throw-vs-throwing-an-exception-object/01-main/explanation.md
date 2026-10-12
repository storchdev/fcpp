# 124 — `throw;` vs. throwing an exception object

## Why the bad code is wrong (`bad.cpp`)

`throw e;` throws a new exception object copy-initialized from the expression `e`, whose static type is `const std::exception&`; the object thrown is a `std::exception`, so the `DiskError` part is sliced off. `throw;` rethrows the currently handled exception object unchanged. The program printed `middle saw: disk full` and then `outer: plain exception, what() = std::exception`: the `catch (const DiskError&)` handler was skipped.

The code compiles without a warning on either compiler under `-Wall -Wextra`, and the program is well-defined. It is a typical refactoring slip (`throw e;` instead of `throw;` in a logging handler), and the visible symptom is a handler that never runs.

## The fix (`good.cpp`)

Use `throw;` to rethrow. The fixed program prints `outer: DiskError`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

