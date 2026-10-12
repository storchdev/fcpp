# 005.02 — Narrowing conversions: silent outside braces

## Why the bad code is wrong (`bad.cpp`)

Only list-initialization forbids narrowing. Copy-initialization (`T x = v;`), direct-initialization with parentheses, assignment, and function arguments all apply the usual implicit conversions ([conv]) and lose information without complaint. `bad.cpp` prints (g++ 16.2, `-std=c++20`):

```
percent=99 level=44 id=705032704 f=16777216.0
```

- `int percent = 99.9;` truncates toward zero: 99, not 100. If the double is out of `int`'s range, the behavior is **undefined**; the example avoids that.
- `std::uint8_t level = 300;` wraps modulo 256 for unsigned types (always defined): 44. g++ warns about this one because it is a constant (`-Woverflow`); clang++ warns too (`-Wconstant-conversion`).
- `std::int32_t id = big;` for a value that does not fit: before C++20 this was implementation-defined; since C++20 the value is the unique one congruent modulo 2^32, so the low 32 bits (705032704 for 5 000 000 000).
- `float f = 16777217;` rounds to the nearest representable float, 16777216.

With `-Wall -Wextra` the non-constant versions of these are not diagnosed at all. `-Wconversion` (and `-Wfloat-conversion`, `-Wsign-conversion`) catch many of them but are noisy, so they are often disabled.

## The fix (`good.cpp`)

- Use `std::lround`, `std::round`, or similar when you want rounding rather than truncation, and make the cast visible.
- For values that come from outside, check the range first with `std::in_range<T>(x)` (C++20, `<utility>`) before casting.
- Initialize with braces wherever the value is a constant, so the compiler checks it (case 01).

## Rust (`good.rs`)

Every lossy conversion is either an explicit `as` (defined, wraps or saturates) or the fallible `TryFrom`/`try_from`, which returns `Err` instead of changing the value silently.
