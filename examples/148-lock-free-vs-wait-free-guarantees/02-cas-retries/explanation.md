# 148.02 — Lock-free vs. wait-free guarantees: CAS retries

## Why the bad code is wrong (`bad.cpp`)

A compare-exchange loop is lock-free (some thread always succeeds when others fail) but not wait-free: a given thread may lose the race again and again. With 8 threads each adding 100000, the worst thread retried 451605 times (g++ `-O0`), 261214 (g++ `-O2`), 606842 (clang++ `-O0`) and 246039 (clang++ `-O2`) in the runs recorded, against 100000 successful operations each; counts vary per run. The result is always correct (`counter = 800000`), so only latency suffers. No bound exists in the standard's guarantee.

There is no data race and nothing to detect; neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Where the operation allows it, use a single RMW such as `fetch_add`, which has no retry loop in the source (whether it is wait-free depends on the generated instruction, which I did not check). The fixed program prints `counter = 800000, no retries in the source`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

