# 084.01 — Implicitly deleted or suppressed special members: destructor suppresses move

## Why the bad code is wrong (`bad.cpp`)

The implicit move constructor is declared only if the class has no user-declared copy operations, move assignment or destructor. `WithDtor` declares a destructor, so it gets no implicit move constructor; `std::move(w)` then selects the implicit copy constructor (which is still generated), and the member `Tracker` is copied. The program printed `move` for `Plain` and `copy` for `WithDtor`, then two `cleanup` lines, with both compilers at `-O0` and `-O2`.

The code is correct but slow: adding a destructor (for logging or a tracing hook) turns every move of the type, and of every class that contains it by value, into a copy. Neither compiler warns under `-Wall -Wextra`. The deprecation warnings do fire if asked: g++ `-Wdeprecated-copy-dtor` ("implicitly-declared ‘WithDtor::WithDtor(const WithDtor&)’ is deprecated") and clang++ `-Wdeprecated-copy-with-user-provided-dtor` ("definition of implicit copy constructor for 'WithDtor' is deprecated because it has a user-provided destructor").

## The fix (`good.cpp`)

Follow the rule of five: if you declare a destructor, also declare (`= default` is fine) the copy and move operations you want. The fixed program prints `move`. Better, avoid user-declared destructors in classes that own nothing directly (the rule of zero).

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
