# 070 — Object slicing

## Why the bad code is wrong (`bad.cpp`)

Initializing a `Shape` object from a `Circle` calls `Shape`'s copy constructor with the `Shape` subobject of the `Circle`. The result is a complete object of type `Shape`: the `Circle` members (`radius`) are not copied, and the dynamic type of the new object is `Shape`, so a virtual call on it runs `Shape::name`. This happens for a by-value parameter (`describe(Shape s)`) and for `vector<Shape>::push_back`, because both copy-initialize a `Shape`. Both compilers printed `by value: Shape` and `in vector: Shape` at `-O0` and `-O2`.

Nothing is undefined and nothing is diagnosed by the compilers: the program is well-formed and merely does something other than the author intended. In real code it is hidden behind a value-semantic container, a `catch (Base e)` clause, or an accidentally copied parameter, and the failure shows up far away as "the override is never called" or as missing state.

`clang-tidy -checks=cppcoreguidelines-slicing` reports it on the `describe(c)` call: "slicing object from type 'Circle' to 'Shape' discards 8 bytes of state" and "... discards override 'name'". Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Pass polymorphic objects by reference or pointer, and store `std::unique_ptr<Base>` (or `shared_ptr`) in containers. Delete the copy operations of the polymorphic base (`Shape(const Shape&) = delete`) so that slicing is a compile error: with that, passing a `Circle` to a by-value `Shape` parameter failed to compile with both compilers ("use of deleted function" in g++, "call to deleted constructor of 'Shape'" in clang++). If copying is needed, provide a virtual `clone()`.

## Rust (`good.rs`)

Rust has no inheritance. A trait object (`dyn Shape`) is unsized and lives behind a pointer (`&dyn Shape`, `Box<dyn Shape>`), so there is nothing to slice: taking one by value is rejected with `E0277` ("the size for values of type `dyn Shape` cannot be known at compilation time"). The demo prints `Circle` in both places.
