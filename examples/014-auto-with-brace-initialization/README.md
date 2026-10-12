# 014 — `auto` with brace initialization

`auto x = {…}` (copy-list-initialization) deduces `std::initializer_list<T>`. `auto x{…}` (direct-list-initialization) requires exactly one element and deduces that element's type. Both compilers I tested (g++ 16.2.1, clang++ 23.1.1) apply the N3922 rules even under `-std=c++11`/`-std=c++14`, so `auto x{1}` is `int` there too; cppreference records this as a defect report applied retroactively.

| Case | What it shows |
| --- | --- |
| `01-copy-list` | `auto a = {42};` is a `std::initializer_list<int>`, `auto b{42};` is an `int`. |
| `02-direct-list-multiple` | `auto x{1, 2};` and `auto y = {1, 2.5};` are ill-formed. |
