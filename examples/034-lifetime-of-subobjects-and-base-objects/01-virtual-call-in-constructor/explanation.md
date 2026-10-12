# 034.01 — Lifetime of subobjects and base objects: a virtual call in a base constructor

## Why the bad code is wrong (`bad.cpp`)

While `Shape::Shape()` runs, the object being constructed is a `Shape`: the `Circle` part does not exist yet. cppreference ("Virtual function specifier", *During construction and destruction*): when a virtual function is called directly or indirectly from a constructor or destructor on the object under construction or destruction, the function called is the final overrider in the constructor's or destructor's class, not one in a more-derived class. So `Circle c;` prints `Shape::describe` from the constructor and only the later explicit `c.describe()` prints `Circle::describe` (g++ 16.2.1 and clang++ 23.1.1, `-std=c++17`). The behavior is defined, but the override the author wrote for this call is never reached. The same applies in destructors.

If the base version were also pure virtual, the call would be case 02.

Detection: clang-tidy `clang-analyzer-optin.cplusplus.VirtualCall` reports `Call to virtual method 'Shape::describe' during construction bypasses virtual dispatch` (verified). No `-Wall -Wextra` warning from either compiler.

## The fix (`good.cpp`)

Do not rely on virtual dispatch in constructors or destructors. Run the virtual operation after construction: from a factory (`create<T>()` in `good.cpp`), from an explicit `init()`, or via a non-virtual interface called by the owner.

## Rust (no equivalent)

Rust has no constructors or inheritance, and a struct value cannot be used before all of its fields are initialized.
