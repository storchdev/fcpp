# 078.02 — RTTI during construction or destruction: a base that is not constructed yet

## Why the bad code is wrong (`bad.cpp`)

In `Widget : Registrar, Observer`, the `Registrar` base is constructed before `Observer`. `Widget()` passes `this` (converted to `Observer*`) to `Registrar`'s constructor, which applies `typeid(*o)` to it. At that point the `Observer` subobject's construction has not begun, and using `typeid` (or `dynamic_cast`) on an object under construction is only defined for the class being constructed and its bases that are already constructed; for anything else the behavior is undefined.

The two compilers behaved differently at `-O0` and `-O2`. g++'s program crashed (segmentation fault, exit status 139 at `-O0`; the plain `-O2` run also dumped core), and `-fsanitize=undefined` reported `load of null pointer of type '<unknown> *'` and `applying non-zero offset 18446744073709551608 to null pointer`: the vptr of `Observer` is still null. clang++'s program printed `registering 6Widget` and exited normally at both levels, and its UBSan reported nothing. I did not investigate why clang++ sees the final type here (an implementation detail, not something the language gives you). g++ also warns at `-O2` with `-Wuninitialized` ("‘w.Widget::<unnamed>.Observer::_vptr.Observer’ is used uninitialized").

Real code does this when a base class registers `this` with a manager in its constructor and the manager then inspects the dynamic type, with multiple inheritance making it work by luck on one compiler.

## The fix (`good.cpp`)

Register after construction (`start()` called by the owner or a factory), when all bases are constructed. The fixed program prints `registering 6Widget` with both compilers.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
