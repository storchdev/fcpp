# 095 — `std::unordered_map` rehashing

## Why the bad code is wrong (`bad.cpp`)

A rehash invalidates all iterators of an unordered container but not references or pointers to its elements. The program saves `it = m.begin()` and `ref = m[7]`, then inserts 100 elements, which forces a rehash (`buckets 29 -> 127` on both compilers). `ref` is still correct (`ref = 7`), but walking from the saved iterator to `end()` visited only 63 of the 120 elements: the iterator's position is tied to the old bucket structure, so the traversal skips elements.

The use of the saved iterator is undefined behavior. It did not crash here (the elements are separately allocated nodes and no sanitizer reports a problem), it just returns a different set of elements than a fresh `begin()`. The result is the same on both compilers at `-O0` and `-O2`; the exact number depends on the library's hashing and growth policy. Neither compiler warns under `-Wall -Wextra`.

The pattern behind it is inserting into the map while iterating it (or keeping `find` results across inserts): the references/pointers guarantee makes people believe iterators are safe too.

## The fix (`good.cpp`)

Get a new iterator after any insertion that can rehash, or `reserve` enough buckets up front (no rehash occurs while the load factor stays below its limit). References and pointers (`ref`) may be kept. The fixed program prints `size = 120, ref = 7, visited = 120`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
