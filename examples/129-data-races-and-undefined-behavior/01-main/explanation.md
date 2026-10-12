# 129 — Data races and undefined behavior

## Why the bad code is wrong (`bad.cpp`)

The C++ memory model defines a **data race** as two conflicting accesses (at least one is a write) to the same memory location, from different threads, with no happens-before relationship between them. A program containing a data race has undefined behavior for the *entire* execution — it isn't limited to "a stale or torn read".

`bad.cpp` has three separate races:

1. `++counter` from two threads. `++` is a load, add, store sequence; two threads interleave and lose updates, so the final count is usually below 200000. That part is the familiar symptom.
2. `ready` is a plain `bool`. The consumer's `while (!ready) {}` loop contains no synchronization, so the compiler is allowed to assume no other thread changes `ready` and hoist the load out of the loop, turning it into an infinite loop (or `if (!ready) for(;;){}`). This is a legal optimization, not a compiler bug. I did not see a hang with either compiler at `-O0` to `-O3` (20 runs each, with a 5 second timeout), so the infinite-loop outcome is permitted but not observed here.
3. `payload = 42` is written before `ready = true`, but without release/acquire ordering, the CPU or compiler may reorder them, and the consumer may observe `ready == true` while still seeing `payload == 0` (or see nothing consistent at all).

The key conceptual point: "it works on x86 in my test" proves little. x86's strong ordering hides some reorderings, but the compiler is free to reorder, merge, or eliminate non-atomic accesses regardless of the CPU. Because the behavior is undefined, even the "benign" races (e.g. a stats counter) can be miscompiled.

ThreadSanitizer (`-fsanitize=thread`) reports two data races with both g++ and clang++: one on `counter` and one on `payload` (read in `main` against the write in the producer). It does not print a separate report for `ready` in the runs I did (three runs each, `-O1`); the `payload` report is the one that exposes the missing synchronization around the flag.

## The fix (`good.cpp`)

- `std::atomic<int>` makes the increments atomic. `memory_order_relaxed` is enough because only the count matters, not ordering relative to other data.
- `ready` becomes `std::atomic<bool>`; the producer does a **release** store and the consumer an **acquire** load. When the acquire load reads the value written by the release store, they *synchronize-with*, which establishes happens-before from `payload = 42` to the consumer's read. `payload` itself can stay non-atomic because that happens-before edge makes the access race-free.
- A `std::mutex` (or `std::condition_variable` instead of the spin loop) is the simpler alternative whenever you don't need lock-free progress.

## Rust (`good.rs`)

Safe Rust statically rules out data races: shared mutable state across threads requires `Sync` types such as atomics or `Mutex`. The racy program can't be written without `unsafe`. The same release/acquire pattern is available through `AtomicBool` with `Ordering`; the stricter type system just forces you to pick an atomic (the payload here is an `AtomicI32` because safe Rust would not let you share a plain `i32` mutably).
