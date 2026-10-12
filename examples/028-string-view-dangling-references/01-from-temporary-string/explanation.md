# 028.01 — `std::string_view` dangling references: a view of a temporary string

## Why the bad code is wrong (`bad.cpp`)

`std::string_view` has an implicit converting constructor from `std::string` (via `operator string_view`), so a function taking `std::string_view` accepts a `std::string` temporary without any visible conversion. `trim_prefix(read_line())` converts the returned temporary into a view, and `trim_prefix` returns a sub-view of its parameter. The temporary `std::string` is destroyed at the end of the full-expression, so `value` points into a freed heap buffer (the string is longer than the small-string buffer).

`value[0]` then reads freed memory: undefined behavior. AddressSanitizer reports `heap-use-after-free` on g++ 16.2.1 and clang++ 23.1.1 (`-std=c++17 -O1`). One caution from this very example: my first version printed the view with `printf("%.*s", …)`, and ASan did *not* report on either compiler (it printed an empty line); indexing the view did. A sanitizer-clean run therefore does not prove a `string_view` use is safe if all reads go through C library calls.

No warning appears under `-Wall -Wextra`, and none of the clang-tidy checks I ran flagged this code. The signature `std::string_view f(std::string_view)` looks as safe as `int f(int)`, which is why reviews miss it. Reviewer rule: a `string_view` that outlives the statement must have a named owner.

## The fix (`good.cpp`)

Keep the `std::string` in a named variable that outlives every view into it; or have the function return `std::string` when the caller needs ownership.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
