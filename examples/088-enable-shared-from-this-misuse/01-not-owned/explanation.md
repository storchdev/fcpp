# 088.01 — `enable_shared_from_this` misuse: object not owned by a `shared_ptr`

## Why the bad code is wrong (`bad.cpp`)

`enable_shared_from_this<T>` holds a `weak_ptr` that is set when the object is first handed to a `shared_ptr`. `shared_from_this()` locks that `weak_ptr`; for an automatic object no `shared_ptr` ever owned it, so the lock fails and `std::bad_weak_ptr` is thrown (since C++17; earlier standards left this undefined). Nothing catches it in `main`, so the program terminated: both compilers printed `terminate called after throwing an instance of 'std::bad_weak_ptr'` and `what():  bad_weak_ptr`, then dumped core, at `-O0` and `-O2`.

The failure is defined, but it is a design trap: the type's interface (`self()`) is callable on any object, while the precondition (it is owned by a `shared_ptr`) lives outside the type. The same exception appears for objects held by `unique_ptr` or stored by value in a container. Neither compiler warns under `-Wall -Wextra`, and no tool was tried.

## The fix (`good.cpp`)

Create the object with `std::make_shared` so a `shared_ptr` owns it from the start. To enforce this, make the constructors private and expose a static factory returning `shared_ptr` (see case 02). The fixed program prints `use_count=2`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
