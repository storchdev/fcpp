# 078.01 — RTTI during construction or destruction: `typeid` in a constructor

## Why the bad code is wrong (`bad.cpp`)

Like virtual calls (entry 072), `typeid` and `dynamic_cast` applied to the object being constructed see the class whose constructor is running. In `Base::Base()`, `typeid(*this)` is the type `Base` and `dynamic_cast<Derived*>(this)` fails and yields a null pointer, because the `Derived` part does not exist yet. After construction `typeid(d)` is `Derived`. The program printed `typeid in Base ctor: 4Base`, a null pointer for the cast, and `typeid after construction: 7Derived` with both compilers at `-O0` and `-O2` (the `4Base`/`7Derived` spelling is the implementation's `name()` string).

This is defined behavior, so it is a logic trap: code that dispatches on dynamic type during construction (registration by type, "am I a Derived?" checks) sees the wrong answer and no compiler or sanitizer says anything. The same applies in destructors once the derived part is destroyed.

## The fix (`good.cpp`)

Ask for the type after the object is complete (from a factory, a separate `init`/`report` call, or the owner). The fixed program prints `typeid after construction: 7Derived`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
