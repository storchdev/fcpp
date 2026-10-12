# 047.02 — Placement new and object replacement: reusing storage without destroying

## Why the bad code is wrong (`bad.cpp`)

`new (&s) std::string(…)` constructs a new string in the storage of `s` while the old string is still alive. cppreference's lifetime page: a program is not required to call a destructor before reusing the storage of an object, and its defect-report list records that, since CWG 2523, this is well-defined even if the program depends on the destructor's side effects. So the placement new itself is not undefined behavior. A `std::string` destructor frees the heap buffer; skipping it means the buffer is leaked, since nothing refers to it any more. The program runs and prints correctly, which makes this class of bug easy to miss.

LeakSanitizer (part of AddressSanitizer on Linux, enabled by default) reports it on both compilers: `ERROR: LeakSanitizer: detected memory leaks` (g++ 16.2.1 and clang++ 23.1.1, `-std=c++17 -O1`). No warning under `-Wall -Wextra`. For a type whose destructor releases something the program depends on (a lock, a file handle, a count), the same pattern is well-defined but leaves that resource held.

## The fix (`good.cpp`)

Call the destructor first (`s.~basic_string();`), then construct the replacement. For ordinary objects, plain assignment (`s = "…"`) is simpler and correct. If a pointer or reference to the old object must continue to work after replacement, see entry 048.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
