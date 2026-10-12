# 148.01 — Lock-free vs. wait-free guarantees: non-lock-free atomic

## Why the bad code is wrong (`bad.cpp`)

`std::atomic<T>` accepts any trivially copyable `T`, but the implementation may protect large types with a hidden lock. The program prints `atomic<Big> is_lock_free = 0, atomic<long> is_lock_free = 1` with g++ at `-O0` and `-O2`. With clang++ the program does not link: `undefined reference to `__atomic_is_lock_free'` at `-O0` and `-O2`; the same program links and prints the same line when `-latomic` is added (checked at `-O2`). The program is well-defined; what surprises is that the type is not lock-free.

Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Check at compile time with `std::atomic<T>::is_always_lock_free` (C++17) and decide on an explicit mutex if it is false. The fixed program uses `static_assert`s and prints `checked at compile time`; it builds with both compilers because it never calls `is_lock_free()`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

