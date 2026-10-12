# 098 — `std::map::operator[]` implicit insertion

## Why the bad code is wrong (`bad.cpp`)

`map::operator[]` is specified as insert-or-find: if the key is absent it inserts a value-initialized element and returns a reference to it. `stock["pear"] == 0` therefore changes the map. The program printed `size before = 1`, `pear is out of stock` and `size after = 2, contains pear: 1` with both compilers at `-O0` and `-O2`: a read-only query added an entry.

Nothing is undefined; the damage is a growing container, wrong `size()`, spurious keys in later iteration, and (for a `const` map) the code does not compile at all because `operator[]` is not a const member. Neither compiler warns under `-Wall -Wextra`, and no tool I ran reported it.

## The fix (`good.cpp`)

Use `find` (as in the good code), `at` (throws `std::out_of_range` for a missing key), or `contains` in C++20. Use `operator[]` only when insertion is intended. The fixed program prints `size after = 1, contains pear: 0`.

## Rust (`good.rs`)

`HashMap` indexing never inserts: a missing key panics ("no entry found for key"). Lookup is `get`, which returns an `Option`, and insertion is the explicit `entry(...).or_insert(...)`. The demo prints `size after = 1` and `size with entry = 2`.
