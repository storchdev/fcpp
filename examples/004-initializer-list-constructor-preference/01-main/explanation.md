# 004 — Initializer-list constructor preference

## Why the bad code is wrong (`bad.cpp`)

In list-initialization ([over.match.list]), overload resolution runs in two phases. In phase one the candidates are *only* the `std::initializer_list` constructors, and the argument is the whole braced list. If any of them is viable, the best one is used, even if another constructor is a far better match for the individual elements. Phase two, which considers all constructors, runs only when phase one found nothing viable.

`Widget w2{10, true}` has an exact match in `Widget(int, bool)`, but `Widget(std::initializer_list<long double>)` is viable because `10` and `true` both convert to `long double`. Phase one finds it, so phase two never happens. The observed output (g++ 16.2, `-std=c++17`) is:

```
Widget(int, bool)                       <- w1(10, true)
Widget(initializer_list<long double>)   <- w2{10, true}
Widget(int, double)                     <- w3(10, 5.0)
Widget(initializer_list<long double>)   <- w4{10, 5.0}
Widget()                                <- w5{}
Widget(initializer_list<long double>)   <- w6{{}}
```

Two more details complete the picture. Empty braces `{}` with a default constructor value-initialize the object, so `w5` calls `Widget()` and not an empty-list constructor. To get an empty list you need `w6{{}}`, as shown. And the preference is applied *before* checking for narrowing. If the only viable `initializer_list` constructor needs a narrowing conversion for the given arguments, the program is ill-formed rather than falling back to another constructor. That makes the choice sensitive to values and types in a way that is hard to predict from a reading of the call site.

This is a trap for class authors as well as callers. Adding an `initializer_list` constructor to an existing class changes the meaning of every existing `{}` call, and nothing flags the change.

## The fix (`good.cpp`)

- Give a class an `initializer_list` constructor only if it is a sequence of elements (a container); then `{}` consistently means "these are the elements".
- Use `()` at call sites that mean "call this constructor". In `good.cpp` the `Widget` class has no `initializer_list` constructor, so `Widget{10, true}` and `Widget(10, true)` agree.
- If you must keep both, provide a named factory or a tag type for the non-list behavior.

Rust has no overloading or implicit list constructors, so this cannot happen.
