# 012.01 — CTAD: copy deduction

## Why the bad code is wrong (`bad.cpp`)

When the initializer is a single expression whose type is already a specialization of the class template being deduced, the *copy deduction candidate* ([over.match.class.deduct]) is preferred over the `initializer_list` guide. So `std::vector grid{row};` with `row` a `std::vector<int>` deduces `std::vector<int>` and makes a copy, rather than a `std::vector<std::vector<int>>` holding one row. Both g++ 16.2 and clang++ 23.1 give that result; the `static_assert`s in `bad.cpp` check it, and the program prints `grid.size=3 grid2.size=2`.

The behavior flips with the number of arguments: `std::vector grid2{row, row};` has two elements, so it deduces `std::vector<std::vector<int>>`. Code that builds a container from a variable number of rows via a helper or a pack (`std::vector{rows...}`) therefore changes type when the pack happens to contain exactly one container. The same applies to other templates: `std::optional p{o};` with `o` a `std::optional<int>` deduces `std::optional<int>`. I checked both the pack case and this one with g++ and clang++.

The type is deduced, so the compiler has no complaint. The failure is usually discovered later, as a size or a template-mismatch error that is far from the line that caused it. Detection: print `decltype(x)` (or a `static_assert`) while debugging; some IDE hints show the deduced type.

## The fix (`good.cpp`)

Spell out the element type when the intent is "one element that is a `T`": `std::vector<std::vector<int>> grid{row};`. Wrapping the argument in another expression of the same type, such as `std::vector{std::vector<int>(row)}`, does not help: it is still a single `std::vector<int>`, so the copy rule applies.

Rust has no CTAD; generics are inferred from expressions, and `vec![row]` always creates a `Vec<Vec<i32>>`.
