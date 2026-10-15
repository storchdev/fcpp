# 185 — Casting away const from an originally const object

## Why the bad code is wrong (`bad.cpp`)

`const_cast` changes the type of an access path; it does not change whether the object itself is const. `limit` was declared `const`, so assigning through `writable` modifies a const object through a non-const glvalue. That is undefined behavior.

The output can be especially misleading. In the runs recorded in `compilers.md`, both compilers printed `limit=7, through reference=9` at both optimization levels. Those values are observations of this build, not a guarantee for undefined behavior. A reviewer should follow the reference back to the original object's declaration. No detection mechanism in this case's checker configuration diagnoses the write.

## The fix (`good.cpp`)

If mutation is required, make the original object mutable and write through its normal non-const access path. Casting away const can be valid when the underlying object was originally non-const, but is unnecessary here.

## Rust (`good.rs`)

Rust requires a mutable binding for this assignment. The commented immutable assignment is rejected with E0384; the runnable version declares `limit` with `mut`.
