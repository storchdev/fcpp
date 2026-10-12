# 147 — `std::atomic_ref` lifetime and alignment

## Why the bad code is wrong (`bad.cpp`)

`std::atomic_ref<T>` applies atomic operations to an ordinary object, but only while every concurrent access to that object goes through atomic operations. Here one thread uses an `atomic_ref<int>` while the other increments the same `int` directly: that is a data race (undefined behavior). The program printed `counter = 150237` (g++ `-O0`) and `179364` (clang++ `-O0`), and `200000` at `-O2` on both compilers, so a plain run can look fine.

TSan reports `data race` at `-O0`, `-O1` and `-O2` with both compilers. Neither compiler warns under `-Wall -Wextra`. This case only covers mixed access; the alignment (`atomic_ref<T>::required_alignment`) and lifetime constraints in the entry are not demonstrated.

## The fix (`good.cpp`)

Route every access during that period through an `atomic_ref` (as in `good.cpp`), or make the variable a `std::atomic<int>` from the start. The fixed program prints `counter = 200000 (expected 200000)`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

