# 085 — Exception safety of move constructors

## Why the bad code is wrong (`bad.cpp`)

When `std::vector` reallocates it moves the existing elements to the new storage only if the move constructor cannot throw (it is `noexcept`) or the type cannot be copied; otherwise it copies them (this is what `std::move_if_noexcept` selects). The reason is exception safety: a throwing move halfway through would leave the old elements already modified, so the vector could not restore its original contents, whereas copying leaves the originals intact. `Item(Item&&)` here is not `noexcept`, so reallocation uses the copy constructor.

The program inserted 100 elements with `emplace_back` and printed `copies=127 moves=0` with both compilers at `-O0` and `-O2`. After adding `noexcept` it printed `copies=0 moves=127`. Both numbers are well-defined; the failure is a silent slowdown (for a type that owns memory, each growth duplicates every element). It is typically written by hand where the compiler would have deduced `noexcept` for a defaulted move, and reviewers miss that the keyword is absent.

Neither compiler warns under `-Wall -Wextra`. `clang-tidy -checks=performance-noexcept-move-constructor` reports it: "move constructors should be marked noexcept".

## The fix (`good.cpp`)

Mark move constructors and move assignments `noexcept` (or default them so the compiler deduces it), and do not allocate or throw inside them. Check with `static_assert(std::is_nothrow_move_constructible_v<T>)`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
