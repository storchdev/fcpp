# 120.01 — Template instantiation across translation units: specialization after use

## Why the bad code is wrong (`bad.cpp`)

If a use would cause an implicit instantiation of `Name<int>`, the explicit specialization must be declared before that use; declaring it later is ill-formed (the standard makes it ill-formed, no diagnostic required, when the use is in another translation unit). Here `first()` instantiates `Name<int>` before the specialization, and both compilers reject it: g++ "specialization of ‘Name<int>’ after instantiation", clang++ "explicit specialization of 'Name<int>' after instantiation".

Only the single-file form was built here. Detection is the compile error.

## The fix (`good.cpp`)

Declare the specialization (in the same header as the primary) before anything that uses it. The fixed program prints `int`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

