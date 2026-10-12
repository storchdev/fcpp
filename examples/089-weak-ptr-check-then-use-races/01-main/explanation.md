# 089 — `weak_ptr` check-then-use races

## Why the bad code is wrong (`bad.cpp`)

`expired()` answers whether the object is gone at that instant; it does not keep it alive. Between `!w.expired()` and `w.lock()` another thread can drop the last owner, and `lock()` then returns an empty `shared_ptr`; `->value` on it is a null pointer dereference, which is undefined behavior. Each of the two calls is individually thread-safe, so ThreadSanitizer has nothing to report: the bug is the pair, a time-of-check/time-of-use gap.

The program forces the interleaving with two `std::promise` handshakes, so the failure is deterministic rather than a rare race. Under `-fsanitize=undefined` both compilers reported `member access within null pointer` at `-O0`, `-O1` and `-O2`. Without the sanitizer, g++ crashed at both `-O0` and `-O2`, clang++ crashed at `-O0`, and clang++ at `-O2` printed `value = 42` (the compiler is allowed to assume the pointer is non-null): another sign that "it worked" proves nothing.

In production code the other thread is a timer or worker releasing a cache entry, and the window is a few instructions wide, so the crash is rare.

## The fix (`good.cpp`)

Take ownership once and test the result: `if (auto sp = w.lock()) { ... }`. `lock()` atomically either returns an owner that keeps the object alive for the whole block, or an empty pointer. `expired()` is only suitable as a hint. The fixed program printed `value = 42` with both compilers.

## Rust (`good.rs`)

`Weak::upgrade` is the only way to reach the value and returns `Option<Arc<T>>`, so the check and the ownership are one operation; there is no separate `expired` to race. The demo prints `value = 42`.
