# 077 — Virtual inheritance layout assumptions

## Why the bad code is wrong (`bad.cpp`)

The layout of an object with virtual bases is not specified by the C++ standard, and in the implementations used here the position of a virtual base subobject is found at run time through the vtable, because it depends on the most-derived class: the same `L` class puts its `V` at one offset when it is a standalone object and at another when it is a base of `D`. The program measures the offset of `V` in a standalone `L` (12 bytes) and then applies it to an `L*` that actually points into a `D`, where the real offset is 32 bytes. The two pointers differ (`guess == real: 0`). Reading through `guess` would be reading a different object's bytes, so the demo prints only `real->v`.

Both compilers printed `sizeof(L)=16 sizeof(D)=40`, offsets `12` and `32`, `guess == real: 0` and `real->v = 7` at `-O0` and `-O2`. Same numbers on both is a property of the ABI both use on this platform, not of the language, and the offsets and sizes can differ on other platforms or compilers.

Related traps are `reinterpret_cast`, bytewise copies of such objects and hard-coded offsets used for serialization or foreign-language interop (not run here). Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Let the compiler convert: `V* v = lp;` computes the right address from the object's real type every time, and the fixed program prints `via L == via R: 1` (the single shared `V`). Do not hard-code offsets, copy such objects bytewise, or use them in standard-layout assumptions.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
