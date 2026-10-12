# 037.02 — Destructor and temporary destruction timing: member destruction order

## Why the bad code is wrong (`bad.cpp`)

After a class's destructor body runs, its non-static data members are destroyed in the reverse order of their declaration. In `Pipeline`, `stage` is declared before `stats`, so `stats` is destroyed first and `stage` second. `Stage::~Stage()` pushes to `stats.samples`, but `stats` (and its vector's buffer) is already gone, so the `push_back` operates on a destroyed `std::vector`: undefined behavior. AddressSanitizer reports `heap-use-after-free` (g++ 16.2.1 and clang++ 23.1.1, `-std=c++17 -O1`).

The mem-initializer list order is irrelevant here; only declaration order counts (see entry 011 for the construction side). `Pipeline() : stage(stats)` also builds `stage` with a reference to a member that is not constructed yet: only safe because `Stage`'s constructor merely stores the reference. Neither compiler warns under `-Wall -Wextra` at `-O0` and `-O1`, g++ emits `-Wuninitialized` at `-O2`, and none of the clang-tidy checks I ran flagged it.

Other destruction-timing rules from the same family, all with defined behavior: temporaries die at the end of the full-expression; locals are destroyed in reverse order of construction at the end of their block (case 01 shows the temporary hazard).

## The fix (`good.cpp`)

Declare dependencies first. With `Stats stats;` before `Stage stage;`, `stage` is destroyed first and its destructor sees a live `stats`. Add a comment (or a design where `Stage` owns its `Stats`) so the ordering survives refactoring.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
