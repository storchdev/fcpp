# 087 — `shared_ptr` ownership cycles

## Why the bad code is wrong (`bad.cpp`)

A `shared_ptr` destroys its object when the strong count reaches zero. After `a->other = b; b->other = a;` each node is held by the other node as well as by the local variable, so when `a` and `b` go out of scope each count drops from 2 to 1 and never reaches 0: neither `~Node` runs, and the memory and anything else the nodes own are leaked. The program printed `a.use_count=2 b.use_count=2` and `build() returned; no ~Node was printed` with both compilers at `-O0` and `-O2`.

This is well-defined, not UB: reference counting cannot reclaim cycles. In real code the cycle is rarely this direct (parent/child links, observers that hold their subject, callbacks capturing `shared_ptr`s to their owner), and the leak is invisible without tooling.

LeakSanitizer (`-fsanitize=address`) reports `Indirect leak` for both nodes with g++ at `-O0`, `-O1` and `-O2`. With clang++ it reported nothing at `-O0` and `-O1` and did report the leak at `-O2` (see `compilers.md`): a leak checker can miss leaks, so absence of a report is not a proof.

## The fix (`good.cpp`)

Make exactly one direction of the relationship owning and the other a `std::weak_ptr` (here `prev`), or use raw non-owning pointers when the owner is known to outlive the reference. The fixed program printed `a.use_count=1 b.use_count=2`, then `~Node` twice before `build() returned`.

## Rust (`good.rs`)

Safe Rust has the same hazard: an `Rc` cycle leaks without any error, because leaking is memory-safe. The same fix applies, with `Weak` for the back-link; the demo prints `a strong=1 weak=1, b strong=2` followed by two `drop Node` lines.
