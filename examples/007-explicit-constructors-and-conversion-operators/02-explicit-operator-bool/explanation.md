# 007.02 — `explicit operator bool`

## Why the bad code is wrong (`bad.cpp`)

A conversion function without `explicit` is used by implicit conversion sequences, and `bool` then promotes to `int` ([conv.prom]), so `Handle` can appear in any expression that accepts a `bool` or an arithmetic type. Here `a == b` compares the two *converted* `bool`s (`true == true`) and `a + b` is `1 + 1`. The program prints `a == b (different descriptors!)` and `open_count=2` (g++ 16.2, `-std=c++17`), with no warning from `-Wall -Wextra`. This is why `std::istream` and standard smart pointers have `explicit operator bool`.

With `explicit operator bool` the conversion is used only where the language says "contextually converted to `bool`" ([conv]): the condition of `if`, `while`, `for`, `do`, the operands of `!`, `&&`, `||`, the first operand of `?:`, and `static_assert`/`noexcept` conditions. It is not used for `bool b = h;`, `return h;` from a `bool` function, passing `h` to a `bool` parameter (all three rejected by g++ and clang++ in my check), `h + 1`, or `h == other`. That asymmetry is the footgun in the other direction: `bool ok() { return handle; }` fails to compile, and the fix is `static_cast<bool>(handle)` or `!!handle`, not removing `explicit`.

Detection: neither compiler warns about the missing `explicit`; clang-tidy has `google-explicit-constructor`, which covers conversion operators too.

## The fix (`good.cpp`)

Declare `explicit operator bool() const`. Then provide the comparisons you actually want (`operator==` here). The contextual forms (`if (a && !b)`) still compile, and `static_cast<bool>(a)` gives the explicit form. The commented lines in `good.cpp` are the ones that become errors.

Rust has no implicit conversions, and `bool` is not produced from user types; you write `h.is_open()` or implement a method.
