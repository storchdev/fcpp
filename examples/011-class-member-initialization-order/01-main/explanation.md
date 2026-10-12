# 011 — Class member initialization order

## Why the bad code is wrong (`bad.cpp`)

The standard fixes the order in which non-static data members are initialized: **the order they are declared in the class body**. The order of the entries in the constructor's mem-initializer list is irrelevant to the actual execution order; the list only supplies the initializers.

In `Buffer`, `data_` is declared before `size_`. The constructor lists `size_(n)` first and `data_(make_unique<int[]>(size_))` second, which reads naturally ("set the size, then allocate that many"). But the compiler constructs `data_` first, so the expression `size_` inside its initializer reads a member whose lifetime has not begun and whose value is indeterminate. That is undefined behavior; typically you get a random (possibly huge or zero) allocation size, so `b.data()[7] = 1` can write out of bounds or `make_unique` can throw `bad_alloc`.

Why it survives code review: the code reads correctly top to bottom, and it often "works" in debug builds where the stack slot happens to contain a sensible value. It also tends to appear during refactors, when someone reorders members for layout or readability without touching the constructor.

Both compilers warn when the list order disagrees with declaration order (g++ `-Wreorder`, clang++ `-Wreorder-ctor`, both on under `-Wall`), and both also warn that `size_` is used uninitialized (`-Wuninitialized`, line 15). That does not catch the case where the list order is "consistent" yet the *declaration* order is wrong for the dependency.

## The fix (`good.cpp`)

Declare members in dependency order (anything used to initialize another member goes first), and where possible initialize from the constructor parameter (`n`) rather than from a sibling member. Keep `-Wall -Werror=reorder` on.

## Rust (`good.rs`)

A struct literal is an ordinary expression; there is no half-built `self` that field initializers can observe, so this class of bug cannot be written in safe Rust.
