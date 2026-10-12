# 099.01 — `insert`, `emplace`, and `try_emplace` semantics: `insert` keeps the old value

## Why the bad code is wrong (`bad.cpp`)

`insert` (and `emplace`, `try_emplace`) add an element only if the key is not already present; they return a `pair<iterator, bool>` whose `bool` reports whether insertion took place. `m.insert({1, 99})` therefore does nothing when key 1 exists, and the code ignores the result. The program printed `m[1] = 10 (wanted 99)` with both compilers at `-O0` and `-O2`.

It is well-defined and silent: neither compiler warns under `-Wall -Wextra`, and no tool I ran reported it. It is a logic bug from reading `insert` as "set".

## The fix (`good.cpp`)

Use `insert_or_assign(key, value)` (C++17) to overwrite, or `m[key] = value` when default construction of the value is acceptable. Check the returned `bool` when insertion-only semantics are intended. The fixed program prints `m[1] = 99`.

## Rust (`good.rs`)

`HashMap::insert` overwrites and returns the previous value as an `Option`; `entry(k).or_insert(v)` keeps the old one. Each is a different method with a visible name, and the demo prints `m[1] = 99, replaced Some(10)` and `m[1] = 99 after or_insert`.
