# 044 — One-past-the-end pointers

## Why the bad code is wrong (`bad.cpp`)

For an array `a` of 4 elements, `a + 4` is a valid pointer value ("a pointer past the end of an object", per cppreference's pointer page). It may be formed, copied and compared, which is what makes half-open loops work. It must not be dereferenced: cppreference's example says `*pxe = 1; // undefined behavior` for such a pointer. The loop condition `p <= a + 4` is inclusive, so the last iteration executes `sum += *p` through exactly that pointer.

AddressSanitizer reports `stack-buffer-overflow` (READ of size 4) on g++ 16.2.1 with `-O1`, and on clang++ 23.1.1 with `-O0`. clang++ at `-O1` printed a garbage sum (`-997251528` in my run) with no report, so use `-O0` there. Neither compiler warns under `-Wall -Wextra`.

A subtlety from the same cppreference page: two pointers that represent the same address may have different values, so a past-the-end pointer of one object is not interchangeable with a pointer to an adjacent object (entry 045).

## The fix (`good.cpp`)

Use half-open ranges: `p != a + 4`, or a range-for. The end pointer is only compared, never read. Standard containers follow the same convention for `end()`.

## Rust (`good.rs`)

A slice iterator yields exactly the valid elements; there is no one-past-the-end pointer to dereference in safe Rust.
