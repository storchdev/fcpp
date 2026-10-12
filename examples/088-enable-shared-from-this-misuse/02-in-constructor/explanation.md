# 088.02 — `enable_shared_from_this` misuse: inside the constructor

## Why the bad code is wrong (`bad.cpp`)

`make_shared<Task>(r)` constructs the `Task` first and only then makes the new `shared_ptr` the owner (which sets the `weak_ptr` inside `enable_shared_from_this`). While the constructor body runs there is no owner yet, so `shared_from_this()` throws `std::bad_weak_ptr`; the exception leaves the constructor and `make_shared`, and with no handler in `main` the program terminated. Both compilers printed `terminate called after throwing an instance of 'std::bad_weak_ptr'` and dumped core at `-O0` and `-O2`, and never printed `created`.

This is the natural place to "register this object with a manager", which is why it is so common. The member function works fine later, so tests that build the object and call it afterwards pass. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Do the registration after the owning `shared_ptr` exists: a private constructor with a static `create` factory that builds the `shared_ptr` first and then registers `t->shared_from_this()`. The fixed program prints `created`. A two-step `init()` called by the owner works too.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
