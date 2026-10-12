# 054 — Invalid pointer use after deallocation

## Why the bad code is wrong (`bad.cpp`)

`delete s;` ends the lifetime of the `Session` and releases its storage. Every pointer that referred to it, including the copy stored in `active`, now holds an invalid pointer value; dereferencing one is undefined behavior. `s` is the pointer that was passed to `delete`, but `active[0]` is a second owner-less alias that has no way to know. The tempting mental model is that the address "still holds a Session"; the storage may be reused or poisoned at any time.

AddressSanitizer reports `heap-use-after-free` (`READ of size 4`) on g++ 16.2.1 and clang++ 23.1.1 (`-std=c++17 -O1`). Neither compiler warns under `-Wall -Wextra` and none of the clang-tidy checks I ran flagged it, since the delete and the use are in different statements connected through a container.

## The fix (`good.cpp`)

Give the object one owner (`std::vector<std::unique_ptr<Session>>`) and make every other access go through that owner while it is alive. Nulling the pointer you deleted only helps that one alias.

## Rust (`good.rs`)

Ownership is unique, and a live borrow prevents dropping the value: `drop(s)` while `r` is alive is `E0505` ("cannot move out of `s` because it is borrowed"), shown commented in `good.rs`.
