# 173 — `std::unordered_map` performance assumptions

## Why the bad code is wrong (`bad.cpp`)

`unordered_map` is average constant time only when keys spread over buckets. With a hash that returns the same value for every key, all elements share one bucket and each insertion scans the whole chain: 20000 inserts took 2714–2727 ms (g++ `-O0`), 274–275 ms (g++ `-O2`), 2619–2633 ms (clang++ `-O0`) and 236–237 ms (clang++ `-O2`) over three runs, versus 0–2 ms for the default hash with a `reserve`. A real-world version of this is a poor custom hash (for example one that drops bits) or adversarial input.

The code is well-defined and neither compiler warns under `-Wall -Wextra`. Other costs not shown here are rehashing, per-node allocation and cache-unfriendly bucket traversal.

## The fix (`good.cpp`)

Use a hash that mixes all bits, `reserve` the expected size, and consider a flat open-addressing container for hot paths. The fixed program uses the default hash with `reserve(20000)`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

