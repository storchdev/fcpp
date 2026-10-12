# 162 — Static destruction order

## Why the bad code is wrong (`bad.cpp`)

Objects with static storage duration are destroyed in the reverse order of the completion of their construction. `service` is constructed at startup without touching the logger; `log()`'s function-local static is constructed on the first call from `main`, so it finishes constructing later and is destroyed earlier. `~Service` then calls `log()`, which returns a reference to the already-destroyed `Logger`; using an object after its destructor has run is undefined behavior. The plain runs printed garbage where the prefix should be (`B%q_: shutting down` for g++ `-O0`, and different bytes on the other runs).

AddressSanitizer reports `heap-use-after-free` at `-O0`, `-O1` and `-O2` with both compilers (the destroyed `std::string` freed its buffer). Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Make the dependency visible to the order of construction: the `Service` constructor calls `log()`, so the logger finishes constructing before the service does and is destroyed after it. The fixed program prints `a prefix long enough to need heap storage, not SSO: shutting down` after the `starting` line, and ASan reports nothing. Other options are a leaked or immortal logger, or an explicit shutdown step.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

