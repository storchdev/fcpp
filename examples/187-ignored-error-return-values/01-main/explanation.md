# 187 — Ignored error return values

## Why the bad code is wrong (`bad.cpp`)

A C++ expression statement may discard an ordinary function's return value. `save_config()` returns `false`, but the caller throws that result away and prints `configuration saved`. The call itself is well defined; the bug is the caller's false success report.

This pattern is easy to miss when a function originally returned `void` or a code review focuses on the call's side effects. Both compilers built this version without warnings under `-Wall -Wextra` at the tested levels. Detect it by reviewing calls to failure-returning APIs and checking that each result controls an appropriate failure path.

## The fix (`good.cpp`)

Check the result before reporting success. `[[nodiscard]]` also asks compilers to warn about future discarded results; it is an aid to callers, not a replacement for handling the failure. Other APIs can use an error code or exception when that better fits their contract.

## Rust (`good.rs`)

The Rust version returns a `Result` and handles its `Ok` and `Err` variants explicitly. Rust's `Result` carries a must-use warning when its value is discarded.
