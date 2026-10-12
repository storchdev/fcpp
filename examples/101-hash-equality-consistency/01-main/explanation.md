# 101 — Hash/equality consistency

## Why the bad code is wrong (`bad.cpp`)

An unordered container finds an element by hashing the key to pick a bucket and then comparing keys in that bucket with the equality predicate. Two keys that compare equal must therefore have the same hash. `CaseInsensitiveEq` treats `"Hello"` and `"HELLO"` as equal, but `std::hash<std::string>` hashes them differently, so they usually land in different buckets: the container requires the pair to hash equally, and it does not, which is undefined behavior.

With 30 other keys in the set the program printed `size = 32 (expected 31), count("hello") = 0 (expected 1)` with both compilers at `-O0` and `-O2`: `"HELLO"` was inserted as a second element, and the lookup for `"hello"` missed. An earlier version of the program with only two keys printed `size = 1` and `count = 1`, i.e. it appeared to work; I did not investigate why small sets behave differently. This is the usual pattern: tests with a few keys pass.

Neither compiler warns under `-Wall -Wextra`, and no sanitizer reports it.

## The fix (`good.cpp`)

Supply a hash that is computed from the same normalized form that equality uses (here lowercasing before hashing). The fixed program prints `size = 31, count("hello") = 1`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
