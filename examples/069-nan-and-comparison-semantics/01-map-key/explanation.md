# 069.01 — NaN and comparison semantics: NaN as a map key

## Why the bad code is wrong (`bad.cpp`)

Every ordered comparison involving a NaN is false (`nan < x`, `nan > x`, `nan == nan` all print `0`), so NaN is not ordered with respect to anything. `std::map` and `std::set` require their comparison to be a strict weak ordering, in which "neither `a < b` nor `b < a`" has to be an equivalence relation. For NaN that relation holds against every value, including `1.0` and `3.0` that are themselves not equivalent, so the requirement is violated and the behavior of the container is undefined.

The observed effect in this program, with both compilers at `-O0` and `-O2`: `m[nan] = 99` did not insert a new element. The tree search found an existing key "equivalent" to NaN and wrote `99` into it, so the entry for `1.0` became `99` and the size stayed `3`. Which key gets overwritten depends on the tree shape; I only observed this one outcome. In a separate test with a `std::set<double>` holding 1, 2 and 3, inserting NaN left the size at 3 with both compilers.

Real programs hit this when measurements or parsed input can contain NaN and are used as keys, deduplicated, or compared with `==`. g++ with `-Wfloat-equal` warns on the `nan == nan` line ("comparing floating-point with ‘==’ or ‘!=’ is unsafe"); clang++ did not warn with the same flag. Neither warns under `-Wall -Wextra`, and no sanitizer applies.

## The fix (`good.cpp`)

Test with `std::isnan` and keep NaN out of ordered containers (reject it or map it to an explicit "missing" representation). Never test for NaN with `==`.

## Rust (`good.rs`)

`f64` is `PartialOrd` but not `Ord`, so `BTreeMap<f64, _>` is rejected at compile time (`E0277`: the trait bound `f64: Ord` is not satisfied). `nan == nan`, `nan < 1.0` and `nan > 1.0` are all `false` as in C++, and you have to decide what NaN means before you can use it as a key.
