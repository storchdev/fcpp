# 017 — Lvalues, prvalues, and xvalues

## Why the bad code is wrong (`bad.cpp`)

Value category is a property of an *expression*, not of the type of a variable. A name that refers to an object is an lvalue expression, even when the variable's declared type is an rvalue reference. In `take(Buffer&& b)` the declared type of `b` is `Buffer&&` (first `static_assert`), but the expression `b` has category lvalue: `decltype((b))` is `Buffer&` (second `static_assert`, which `decltype` of a parenthesized expression gives as `T&` for lvalues, `T&&` for xvalues, `T` for prvalues).

Overload resolution and initialization look at the expression's category, so `consume(b)` selects `consume(const Buffer&)` and `Sink s(b)` copy-constructs. Observed output (g++ 16.2.1 and clang++ 23.1.1, `-std=c++17`): `consume(const Buffer&)`, `copy`, `move`. The `copy` is `b` into `Sink`'s by-value parameter; the `move` that follows is that parameter into the member. Nothing is wrong with the program's memory; it simply copies a 40-byte string the author meant to hand over, and nothing warns under `-Wall -Wextra`.

The three categories you meet in practice: **lvalue** (names, `*p`, `a[i]`); **prvalue** (literals, `make()`, arithmetic results; it initializes an object); **xvalue** (`std::move(x)`, a member of a prvalue such as `make().data`; an object whose resources can be reused). `good.cpp` checks each with `static_assert(std::is_same_v<decltype((expr)), …>)`.

Detection: clang-tidy `cppcoreguidelines-rvalue-reference-param-not-moved` reports `rvalue reference parameter 'b' is never moved from inside the function body`; I ran it on `bad.cpp`.

## The fix (`good.cpp`)

Apply `std::move` to the parameter at its last use: `Sink s(std::move(b));` casts the lvalue back to an xvalue. `consume(b)` stays an lvalue use on purpose, so the object is intact for the later move. Do not move on every use (see entries 020 and 023).

## Rust (`good.rs`)

Rust has no value categories. A by-value parameter is owned; passing it on moves it, and using it afterwards is `E0382` (shown as a comment). There is no state where a name of "rvalue type" silently picks the copying path.
