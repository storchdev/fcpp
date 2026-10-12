# 126.01 — `std::optional::value()` and `std::expected::value()`: dereferencing an empty optional

## Why the bad code is wrong (`bad.cpp`)

`operator*` and `operator->` on an `optional` have the precondition that it contains a value; with none, the behavior is undefined. `value()` is the checked accessor and throws `std::bad_optional_access`. Here `(*name).size()` reads a `std::string` that does not exist. What happens depends on the build: in this environment both compilers aborted at `-O0` with a libstdc++ assertion (`this->_M_is_engaged()` failed in `optional`), while at `-O2` g++ printed `length = 0` and clang++ printed an empty line. I did not find out why the assertion is active at `-O0` by default here.

Neither compiler warns under `-Wall -Wextra`, and no sanitizer applies.

## The fix (`good.cpp`)

Test first (`if (name)`), use `value_or`, or use `value()` where an exception is the intended failure. The fixed program prints `length = 0`.

## Rust (`good.rs`)

`Option` has no unchecked dereference: `*name` is rejected (`E0614`: type `Option<String>` cannot be dereferenced), so every access must say what happens for `None` (`unwrap_or`, `match`, or `unwrap`, which panics with "called `Option::unwrap()` on a `None` value"). The demo prints `length = 0`.

