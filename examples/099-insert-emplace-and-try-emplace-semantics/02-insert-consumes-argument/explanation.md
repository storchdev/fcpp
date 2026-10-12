# 099.02 — `insert`, `emplace`, and `try_emplace` semantics: `insert` consumes its argument

## Why the bad code is wrong (`bad.cpp`)

`m.insert({1, std::move(job)})` builds a `pair<int, unique_ptr<int>>` from `job` before `insert` runs, so `job` is moved from regardless of whether the key exists. Key 1 is already present, nothing is inserted, and the temporary pair is destroyed with the `unique_ptr` inside it: the object `job` owned is deleted and `job` is null. The program printed `job is gone (null)` with both compilers at `-O0` and `-O2`.

In a scratch test with the same key, `emplace(1, std::move(q))` and `try_emplace(1, std::move(r))` left their arguments intact on both compilers; I did not check whether `emplace` is guaranteed to behave this way, which is why the fix uses `try_emplace`, the function documented for "do not touch the arguments if the key exists" (see the cppreference page). Nothing is undefined, and neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use `try_emplace(key, args...)`: when the key exists it does not move from `args`. The fixed program prints `job is still owned here`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
