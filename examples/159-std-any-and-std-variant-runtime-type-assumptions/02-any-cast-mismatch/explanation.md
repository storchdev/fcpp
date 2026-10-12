# 159.02 — `std::any` and `std::variant` runtime type assumptions: `any_cast`

## Why the bad code is wrong (`bad.cpp`)

`std::any` stores the exact type it was given. `std::any a = "hello"` stores a `const char*`, so `any_cast<std::string>(a)` throws `std::bad_any_cast`; unlike `variant`, there is no list of alternatives for the compiler to check. The program printed `bad_any_cast: bad any_cast` with both compilers at `-O0` and `-O2`.

The code is well-defined. g++ at `-O2` emits `[-Warray-bounds=]` inside libstdc++ (`array subscript ‘const std::__cxx11::basic_string<char>[0]’ is partly outside array bounds of ‘void [6]’`) for the dead branch; clang++ emits no warning.

## The fix (`good.cpp`)

Store the type you will ask for (`std::string("hello")`), and use the pointer form `any_cast<T>(&a)`, which returns `nullptr` on mismatch instead of throwing. The fixed program prints `hello`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

