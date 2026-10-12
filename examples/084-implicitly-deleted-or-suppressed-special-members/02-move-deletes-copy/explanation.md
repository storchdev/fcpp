# 084.02 — Implicitly deleted or suppressed special members: move deletes copy

## Why the bad code is wrong (`bad.cpp`)

If a class declares a move constructor or move assignment operator and does not declare a copy constructor, the implicit copy constructor is defined as deleted. `Handle` declares only `Handle(Handle&&)`, so `Handle b = a;` selects a deleted function and the program is ill-formed. Both compilers reject it at `-O0` and `-O2`: g++ "use of deleted function ‘constexpr Handle::Handle(const Handle&)’", clang++ "call to implicitly-deleted copy constructor of 'Handle'".

This is the usual and sensible way to make a move-only type, but it surprises people who add a move constructor to an existing copyable class, since the copy that used to work stops compiling at distant call sites. The messages do not say that the move constructor caused it.

## The fix (`good.cpp`)

If the type should stay copyable, declare the copy constructor explicitly (`Handle(const Handle&) = default;`, or a real copy that duplicates the resource); if it should be move-only, say so with `= delete` so the intent is visible. The fixed program builds and exits 0.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
