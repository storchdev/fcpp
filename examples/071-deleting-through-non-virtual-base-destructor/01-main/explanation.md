# 071 — Deleting through a non-virtual base destructor

## Why the bad code is wrong (`bad.cpp`)

If a `delete` expression's operand has static type `Base*` and the object has a different dynamic type, the behavior is undefined unless `Base` has a virtual destructor. With a non-virtual destructor, `delete p` calls only `~Base` (the program printed just `~Base` at `-O0` and `-O2` with both compilers), so `~Derived` never runs and the `std::string payload` it owns is never destroyed. Because the object is deallocated with the size of `Base`, the allocation size is also wrong.

Running the same program under AddressSanitizer, both compilers stop with `new-delete-type-mismatch` at `-O0`, `-O1` and `-O2`; g++'s report says "size of the allocated type: 40 bytes; size of the deallocated type: 8 bytes". With that check turned off (`ASAN_OPTIONS=new_delete_type_mismatch=0`), LeakSanitizer reports `101 byte(s) leaked in 1 allocation(s)` from both compilers: the 100-character string plus its terminator. A plain run shows no symptom, which is why this survives: the leak is small, and without a sanitizer the allocator may not mind the wrong size.

Both compilers warn under `-Wall -Wextra` when the base is polymorphic, as here: g++ `-Wdelete-non-virtual-dtor` ("deleting object of polymorphic class type ‘Base’ which has non-virtual destructor might cause undefined behavior") and clang++ `-Wdelete-non-abstract-non-virtual-dtor`. The warning needs a virtual function in `Base`, and my first version without one produced no warning from either compiler. `clang-tidy -checks=cppcoreguidelines-virtual-class-destructor` flags the class declaration itself ("destructor of 'Base' is public and non-virtual").

## The fix (`good.cpp`)

Make the base destructor `virtual` if anyone can delete through a `Base*`, or hold the object in `std::unique_ptr<Base>`/`shared_ptr` (with `unique_ptr<Base>` the destructor still has to be virtual; `shared_ptr` captures the right deleter at construction). If the base is never deleted polymorphically, a protected non-virtual destructor makes the misuse a compile error. The fixed program prints `~Derived` then `~Base`.

## Rust (`good.rs`)

A `Box<dyn Base>` always drops the concrete type, so there is no "virtual destructor" to forget: the demo prints `drop Derived (100 bytes)` for a value dropped through the trait object.
