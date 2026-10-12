# 069.02 — NaN and comparison semantics: `std::sort` with NaN

## Why the bad code is wrong (`bad.cpp`)

`std::sort` requires its comparison to be a strict weak ordering. `operator<` on `double` is one only when no NaN is present: with a NaN, "incomparable" is not transitive (`nan` is incomparable to `1` and to `2`, but `1 < 2`). Violating the requirement is undefined behavior, so the algorithm is free to produce any result; it is not merely "NaN ends up somewhere".

In this program both compilers, at `-O0` and `-O2`, produced `0 1 2 3 4 5 6 7 9 nan 8 nan 10 11 12 13 14 15 16 17`: `9` before `8`, which is plainly unsorted, and yet `std::is_sorted` returned `1`, because it only checks that no neighbouring pair is out of order according to the same broken comparison. Nothing crashed: AddressSanitizer reported nothing for a similar program, and `-D_GLIBCXX_DEBUG` with g++ did not abort either, so these tools do not find the problem. Other inputs or library implementations may crash (not observed here).

It survives review because the data usually has no NaN until one arrives from parsing or a division, and the sort call looks harmless. Detection is by tests with NaN input or by checking for NaN before sorting.

## The fix (`good.cpp`)

Either remove NaNs first, or sort with a comparator that is a strict weak ordering over all values: `nan_last` treats every NaN as greater than any number and all NaNs as equivalent. The demo prints the numbers in order followed by the two NaNs.

## Rust (`good.rs`)

`v.sort()` on a `Vec<f64>` does not compile (`E0277`, `f64: Ord` is not satisfied). `sort_by(f64::total_cmp)` makes the choice explicit: the demo prints the numbers ascending followed by `NaN, NaN`.
