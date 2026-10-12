# 127 — `std::variant` exceptional states

## Why the bad code is wrong (`bad.cpp`)

Assigning `v = t` destroys the current `std::string` and then copy-constructs the `Thrower` alternative, which throws. The variant has no active alternative any more: it is *valueless by exception*, `valueless_by_exception()` is `true` and `index()` is `std::variant_npos`. The program printed `valueless = 1, index = 18446744073709551615` and then `visit threw: std::visit: variant is valueless`: `std::visit` throws `std::bad_variant_access` for a valueless variant, and `std::get` and `std::get_if` also stop behaving as for a normal alternative.

Code that assumes "a variant always holds exactly one alternative" is wrong after any throwing assignment or `emplace`. Output was identical on both compilers at `-O0` and `-O2`; neither warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Check `valueless_by_exception()` after a failed modification and give the variant a value, or make the alternatives' copy/move nothrow so it cannot happen. The fixed program prints `valueless = 0, index = 0`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

