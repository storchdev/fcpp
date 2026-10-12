# 012.02 — CTAD: string literals deduce as `const char*`

## Why the bad code is wrong (`bad.cpp`)

CTAD uses ordinary template argument deduction on the synthesized guides. A string literal has type `const char[N]`; for a by-value parameter it decays to `const char*`. So `std::vector names{"bob", "alice"};` is `std::vector<const char*>` and `std::pair entry{"id", 42};` is `std::pair<const char*, int>`. The `static_assert`s in `bad.cpp` check this with g++ 16.2 and clang++ 23.1.

This is a problem because `const char*` has pointer semantics. `names[0] == input.c_str()` compares addresses, not characters: with `std::string input = "bob";` it prints `0` even though the text is equal (both compilers). `std::sort(names.begin(), names.end())` sorts by address, `std::find` may find nothing, `std::map` keys of `const char*` are looked up by pointer, and the vector's elements are only valid as long as the pointed-to strings are, which is fine for literals and a dangling pointer for anything else. Whether two equal literals share storage is unspecified, so a pointer comparison of two literals may be true on one build and false on another.

Parentheses make it worse. With `()`, CTAD does not use the `initializer_list` guide, and for two arguments of the same type the iterator-pair guide `vector(InputIt, InputIt)` is viable. `std::vector("bob", "alice")` therefore deduces `std::vector<char>` (the `decltype` `static_assert` at the end of `bad.cpp`, which only names the type and never constructs the object). Actually evaluating that expression would treat the two unrelated literals as an iterator range, which is undefined. Don't run it.

## The fix (`good.cpp`)

Write the type: `std::vector<std::string>`, or give CTAD a `std::string` to deduce from, using the `s` literal suffix from `std::literals::string_literals` (C++14): `std::vector{"bob"s, "alice"s}`. For `std::string_view` use the `sv` suffix. In both cases the comparison is then textual.

## Rust (no `good.rs`)

Rust string literals are `&'static str`, which compares by content, and there is no pointer-comparison pitfall for `==` on string types.
