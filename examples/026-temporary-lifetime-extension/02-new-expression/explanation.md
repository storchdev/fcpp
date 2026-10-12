# 026.02 — Temporary lifetime extension: a `new` expression

## Why the bad code is wrong (`bad.cpp`)

`Label on_stack{std::string("…")};` aggregate-initializes a named object with a braced list; the temporary bound to the reference member `text` is extended to the lifetime of `on_stack`. The same braced initializer in a new-expression does not get that treatment. cppreference: "a temporary bound to a reference in the initializer used in a new-expression exists until the end of the full expression containing that new-expression, not as long as the initialized object. If the initialized object outlives the full expression, its reference member becomes a dangling reference."

So `heap->text` refers to a `std::string` that was destroyed at the `;` after `new Label{…}`. Reading it is undefined behavior; both compilers' ASan reports `stack-use-after-scope` (`-std=c++20`, `-O1`). The first line, through `on_stack`, prints correctly. Note the two lines use the same syntax apart from `new`; that is why it is easy to miss in review.

Detection: clang++ 23.1.1 warns under `-Wall -Wextra`: `warning: temporary bound to reference member of allocated object will be destroyed at the end of the full-expression [-Wdangling-field]`. g++ 16.2.1 gave no warning for `bad.cpp` under `-Wall -Wextra` at `-O0`; at `-O1` and `-O2` g++ emits `-Wdangling-pointer=` and `-Wuninitialized` (both reported inside `<bits/basic_string.h>`, not on a line of this program).

## The fix (`good.cpp`)

Make the member own its data (`std::string text;`). Reference members in objects that can outlive the full-expression that built them are rarely a good idea; use `std::make_unique` for heap allocation instead of raw `new`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
