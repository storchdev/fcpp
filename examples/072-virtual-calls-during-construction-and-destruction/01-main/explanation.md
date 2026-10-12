# 072 — Virtual calls during construction and destruction

## Why the bad code is wrong (`bad.cpp`)

While a constructor or destructor of class `X` runs, the object's dynamic type is `X`: virtual calls resolve as if the object were an `X` (the final overrider in `X` or its bases), not the most-derived class. In `Base::Base()` the call `name()` therefore runs `Base::name`, because the `Derived` part does not exist yet; in `Base::~Base()` the `Derived` part has already been destroyed, so again `Base::name` runs. The program printed `Base ctor: Base`, `main: Derived`, `Base dtor: Base` with both compilers at `-O0` and `-O2`.

This is well-defined, which is why it is a trap: the code compiles, runs and gives a plausible but wrong answer. It matters most for "template method" initialization (`Base()` calls a virtual `init()` that subclasses are supposed to override) and for logging in destructors.

Neither compiler warns under `-Wall -Wextra`. `clang-tidy -checks=clang-analyzer-optin.cplusplus.VirtualCall` reports both calls: "Call to virtual method 'Base::name' during construction bypasses virtual dispatch" and the same for destruction.

## The fix (`good.cpp`)

Do not rely on virtual dispatch from constructors or destructors. Use two-phase initialization (call `init()` after construction, ideally from a factory function so it cannot be forgotten), pass the needed data to the base constructor, or call a non-virtual function explicitly.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
