# 150 — Lazy ranges and repeated evaluation

## Why the bad code is wrong (`bad.cpp`)

A range adaptor such as `views::transform` stores the callable and applies it each time an element is dereferenced; it does not cache results. Iterating `squares` twice therefore runs the lambda twice per element, and any side effects or cost are repeated. The program printed `sum = 60, transform ran 8 times for 4 elements` with both compilers at `-O0` and `-O2`.

The code is well-defined. It is easy to miss in review because the view looks like a container. Neither compiler warns under `-Wall -Wextra`, and no tool I ran flags it.

## The fix (`good.cpp`)

Materialize the results once into a container when the range is used more than once or when the callable has side effects or cost. The fixed program prints `sum = 60, transform ran 4 times for 4 elements` with both compilers.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

