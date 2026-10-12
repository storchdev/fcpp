# 055.02 — Over-aligned allocation and packed structures: a pointer to a packed member

## Why the bad code is wrong (`bad.cpp`)

`__attribute__((packed))` (a GCC/clang extension) removes padding, so `Record::value` sits at offset 1 with alignment 1. `&r.value` has type `int*`, and code that receives an `int*` is entitled to assume 4-byte alignment; `set` dereferences it, which is a misaligned access: undefined behavior. Accessing `r.value` directly is fine because the compiler knows the member is packed; the problem begins when the address escapes into an ordinary pointer.

Both compilers warn under `-Wall -Wextra`: g++ 16.2.1 `warning: taking address of packed member of ‘Record’ may result in an unaligned pointer value [-Waddress-of-packed-member]`; clang++ 23.1.1 `warning: taking address of packed member 'value' of class or structure 'Record' may result in an unaligned pointer value [-Waddress-of-packed-member]`. clang++ with `-fsanitize=undefined` also reports `runtime error: store to misaligned address … for type 'int', which requires 4 byte alignment`; g++ with `-fsanitize=undefined` printed no report for the same program (it ran and printed `3`), which is why `bad.cpp` has no sanitizer header and the warnings are the verified detection.

## The fix (`good.cpp`)

Don't form `int*` to packed members: access the member directly (`r.value += 1`), or copy through `std::memcpy` (shown). If the layout must be fixed for a wire format, parse and serialize the bytes explicitly (entry 042) and keep the in-memory type naturally aligned.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
