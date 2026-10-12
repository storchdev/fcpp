# 168 — Hidden dynamic allocations

## Why the bad code is wrong (`bad.cpp`)

`record(const std::string&)` looks cheap, but passing a string literal builds a temporary `std::string` for every call, and text longer than the small-string buffer needs a heap allocation. The program replaces global `operator new` with a counting version and printed `allocations = 1000, total = 53000` with both compilers at `-O0` and `-O2`: one allocation per call. Nothing at the call site shows it.

The code is well-defined. Neither compiler warns under `-Wall -Wextra`. Finding it takes an allocation counter like this one, or a profiler (not run here).

## The fix (`good.cpp`)

Take `std::string_view` when the function only reads the text. The fixed program printed `allocations = 0, total = 53000`. The same pattern applies to `std::vector` parameters, `std::function`, `std::to_string` and returning containers by value in hot paths.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

