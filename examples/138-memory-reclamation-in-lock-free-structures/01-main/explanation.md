# 138 — Memory reclamation in lock-free structures

## Why the bad code is wrong (`bad.cpp`)

The CAS that unlinks a node is atomic, but another thread may have loaded the node's address earlier and still intends to read it. The program models that with the `preempted` hook: the outer pop loads `old`, then the inner pop unlinks and `delete`s the same node, and the outer pop reads `old->next` from freed memory, which is undefined behavior. A plain run printed `popped 2` with both compilers at `-O0` and `-O2`, because the freed bytes were still intact.

AddressSanitizer reports `heap-use-after-free` at `-O0`, `-O1` and `-O2` with both compilers. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Do not free a node while any thread may still read it: defer reclamation with hazard pointers, epoch-based reclamation or reference counting, or recycle through a quiescent point. The good program keeps unlinked nodes on a retire list and frees them only at a point where no thread is inside `pop` (a simplified stand-in for those schemes); it prints `popped 2` and ASan reports nothing.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

