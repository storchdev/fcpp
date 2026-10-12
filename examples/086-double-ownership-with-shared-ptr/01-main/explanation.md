# 086 — Double ownership with `std::shared_ptr`

## Why the bad code is wrong (`bad.cpp`)

Each `std::shared_ptr` constructed from a raw pointer allocates its own control block with its own reference count. `a` and `b` both own `raw`, but neither knows about the other, so each reports `use_count() == 1` and each deletes `raw` when its count reaches zero. The second `delete` is a double free, which is undefined behavior. The program printed `a.use_count=1 b.use_count=1`, then `~Widget` twice (stdout unbuffered), and aborted with glibc's `free(): double free detected in tcache 2` at `-O0` and `-O2` with both compilers.

It looks innocent because the raw pointer is an ordinary local and each `shared_ptr` is individually correct. It appears in real code when a raw pointer is passed around for "convenience" and later wrapped again, or when `shared_ptr<T>(this)` is used inside a member function.

AddressSanitizer reports `attempting double-free` at `-O0`, `-O1` and `-O2` with both compilers. Neither compiler warns. `clang-tidy -checks=cppcoreguidelines-owning-memory` flags the origin: "initializing non-owner 'Widget *' with a newly created 'gsl::owner<>'".

## The fix (`good.cpp`)

Create the owner with `std::make_shared` (the raw pointer never exists) and share by copying the `shared_ptr`; both then have `use_count() == 2` and the object is destroyed once. If a member function needs a `shared_ptr` to `*this`, derive from `std::enable_shared_from_this` (see entry 088).

## Rust (`good.rs`)

`Rc::from(w)` consumes the `Box`, so a second `Rc::from(w)` is rejected with `E0382` ("use of moved value: `w`"); sharing is `Rc::clone`, and the demo prints `strong_count a=2 b=2` and a single `drop Widget 1`.
