# 182 — Microbenchmark distortions

## Why the bad code is wrong (`bad.cpp`)

`sum` is computed but never read, so at `-O2` the optimizer deletes the loop: both compilers reported `1000000000 iterations took 60 ns` at `-O2`, while at `-O0` (nothing removed) g++ took 689106066 ns and clang++ 1511379928 ns in one run each. The benchmark measured nothing. Other distortions (inlining differences, constant folding, warm caches, frequency scaling) are not demonstrated here.

Both compilers warn under `-Wall -Wextra`: g++ `variable ‘sum’ set but not used [-Wunused-but-set-variable=]`, clang++ `variable 'sum' set but not used [-Wunused-but-set-variable]`, which is a hint that the result is not used.

## The fix (`good.cpp`)

Make the result observable and stop the optimizer from deleting or folding the work: consume the result (print it) and use an optimization barrier such as `asm volatile("" : "+r"(sum))` (GCC/Clang extension) or a benchmark library's `DoNotOptimize`. The fixed program took 792393852 ns (g++ `-O0`), 198686225 ns (g++ `-O2`), 1523778795 ns (clang++ `-O0`) and 197605338 ns (clang++ `-O2`) in one run each, and prints the sum.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

