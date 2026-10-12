# 176.02 — Hidden copies in range-based loops: `vector<bool>` proxy

## Why the bad code is wrong (`bad.cpp`)

`std::vector<bool>` does not store `bool` objects; `*it` returns a proxy by value (`std::_Bit_reference` in libstdc++). A non-const lvalue reference `auto&` cannot bind to that temporary, so the loop is ill-formed. Both compilers reject it. g++: `error: cannot bind non-const lvalue reference of type ‘std::_Bit_reference&’ to an rvalue of type ‘std::_Bit_iterator::reference’`. clang++: `error: non-const lvalue reference to type 'reference' (aka '_Bit_reference') cannot bind to a temporary of type 'reference' (aka '_Bit_reference')`.

The silent variant is `for (auto f : flags)`, which copies the proxy (a reference to a bit), so modifications still reach the vector, unlike for other element types.

## The fix (`good.cpp`)

Use `auto&&` (a forwarding reference binds to the proxy temporary; as in `good.cpp`) or an explicit `for (bool f : flags)` for reading. The fixed program prints `set = 8`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

