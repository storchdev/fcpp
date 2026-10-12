# 031 — Dangling lambda captures

## Why the bad code is wrong (`bad.cpp`)

`[&count]` stores a reference (in practice, the address) to the local `count` inside the closure object. The closure is returned (wrapped in a `std::function`) and outlives `make_counter`; its `count` ceased to exist when the function returned. Calling `next()` increments and reads a dead stack slot: undefined behavior. AddressSanitizer with `ASAN_OPTIONS=detect_stack_use_after_return=1` reports `stack-use-after-return` on g++ 16.2.1 and `stack-use-after-scope` on clang++ 23.1.1 (`-std=c++17 -O1`).

It is easy to write because the lambda body looks identical for `[&]` and `[=]`, and the same lambda is correct if it is only called inside the function. The danger is the closure escaping: returned, stored in a container or a member, or handed to `std::thread`/`std::async`/a callback queue that runs later. Neither compiler warns under `-Wall -Wextra` in this form at `-O0` and `-O1`; at `-O2` g++ emits `-Wuninitialized` and clang++ nothing. clang-tidy's static analyzer reports it: `clang-analyzer-core.StackAddressEscape`: `Address of stack memory associated with local variable 'count' returned to caller` (verified on `bad.cpp`).

## The fix (`good.cpp`)

Capture by value, with an init-capture when the closure needs its own mutable state: `[count = start]() mutable { return ++count; }`. By-value captures are copied into the closure, so it owns them. When a reference capture is truly wanted (a closure used only within the scope), make that the explicit, local choice.

## Rust (`good.rs`)

A closure that borrows `count` and is returned is rejected with `E0373` ("closure may outlive the current function"); `move` transfers ownership into the closure. The rejected form is shown commented in `good.rs`.
