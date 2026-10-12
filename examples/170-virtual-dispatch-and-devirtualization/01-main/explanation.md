# 170 — Virtual dispatch and devirtualization

## Why the bad code is wrong (`bad.cpp`)

`s->area(i & 15)` goes through the vtable of a `Shape` pointer returned from a `noinline` factory, so the call stays indirect and cannot be inlined in `main` at `-O0` (and often not at higher levels). With a `final` class used directly the compiler knows the target and can inline. Timings for 100000000 calls, three runs each: g++ `-O0` 741–743 ms (bad) vs 98–107 ms (good); g++ `-O2` 39 vs 19–24 ms; clang++ `-O0` 752–754 vs 141–142 ms; clang++ `-O2` 98 vs 15 ms.

The cost is not the virtual call alone but lost inlining and the optimizations that follow from it; at `-O2` g++ was much closer than clang++ here (I did not inspect the generated code to say why). The code is well-defined and neither compiler warns under `-Wall -Wextra`. Measure with your own types and optimization level before restructuring a design for it.

## The fix (`good.cpp`)

Where the dynamic type is known or fixed, mark classes and overriders `final` so the compiler can devirtualize, use the concrete type (or a template/CRTP) in hot loops, and keep the virtual interface for the places that need it. The fixed program computes the same sum with a direct call on a `final` type.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

