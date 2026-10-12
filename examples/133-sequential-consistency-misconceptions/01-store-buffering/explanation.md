# 133.01 — Sequential consistency misconceptions: store buffering

## Why the bad code is wrong (`bad.cpp`)

Each thread stores 1 to its own variable and then loads the other's. With `memory_order_seq_cst` on all four operations there is a single total order, so at least one load must see 1. With release stores and acquire loads there is no such order: nothing forbids both loads from reading 0, which is permitted by the memory model. The program counts how often that happens over 200000 rounds. Observed in plain runs: g++ `-O0` 0 and `-O2` 11755 to 31645; clang++ `-O0` 194 to 8388 and `-O2` 853 to 27763 (three runs each; the count varies and can be 0, as it was for every g++ `-O0` run).

So the reordering is permitted by the model and was observed here, but this is not a guarantee that any given run shows it. Nothing is a data race (all variables are atomic) and no tool flags it; neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use `seq_cst` (the default) for the store and load pair, or a `seq_cst` fence between them. The fixed program printed `both loads saw 0 in 0 of 200000 rounds` with both compilers at `-O0` and `-O2` (and in each of the runs I did). The cost is stronger barriers on some architectures; I did not measure it.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

