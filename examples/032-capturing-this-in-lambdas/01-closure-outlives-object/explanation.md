# 032.01 — Capturing `this` in lambdas: the closure outlives the object

## Why the bad code is wrong (`bad.cpp`)

Inside a member function, `[=]` copies local variables and *implicitly captures `this`* when the body uses a member. What is copied is the `Widget*` pointer, not the object. `callbacks` stores the closure after `arm()` returns, `delete w` destroys the widget, and the later call reads `this->clicks` through the stale pointer: undefined behavior. AddressSanitizer reports `heap-use-after-free` on g++ 16.2.1 and clang++ 23.1.1 (`-std=c++20 -O1`).

In C++20 the implicit capture of `this` by `[=]` is deprecated, and both compilers say so under `-Wall -Wextra`: g++ `warning: implicit capture of ‘this’ via ‘[=]’ is deprecated in C++20 [-Wdeprecated]`, clang++ `warning: implicit capture of 'this' with a capture default of '=' is deprecated [-Wdeprecated-this-capture]`. clang-tidy `cppcoreguidelines-misleading-capture-default-by-value` also reports it (`lambdas that implicitly capture 'this' should not specify a by-value capture default`). The warnings point at the capture, but not at the lifetime problem itself.

The shape is common in event handlers, timers and async callbacks registered in a constructor or method, with the object destroyed before the event fires.

## The fix (`good.cpp`)

`[*this]` (C++17) captures a copy of the whole object, so the closure owns its state. That is only right if a snapshot is acceptable. When the closure must observe the live object, tie the lifetimes: hold the object in a `std::shared_ptr` (via `enable_shared_from_this`) and capture `shared_from_this()` or a `weak_ptr`, or unregister the callback in the destructor.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
