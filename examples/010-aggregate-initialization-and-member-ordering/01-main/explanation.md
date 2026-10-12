# 010 — Aggregate initialization and member ordering

## Why the bad code is wrong (`bad.cpp`)

An aggregate ([dcl.init.aggr]) is a class with no user-provided constructors (in C++20, no user-declared ones), no private or protected non-static data members, and no virtual functions. Initializing one with a braced list assigns the initializer clauses to the members **in declaration order**. If there are fewer clauses than members, the remaining members are initialized from an empty initializer list, which for `int` means zero.

Both rules are silent footguns:

- **Reordering members changes meaning without breaking the build.** `before::Window{800, 600, 2}` means width 800, height 600, border 2. After the struct is reordered to `{border, height, width}`, the same text compiles and means border 800, width 2. All three members are `int`, so the types give no warning. Observed output (g++ 16.2):
  ```
  a: 800x600 border=2
  b: 2x600 border=800
  c: 0x600 border=800
  ```
- **Missing trailing initializers are allowed.** `after::Window c{800, 600}` leaves `width` at zero. g++ warns with `-Wmissing-field-initializers` (enabled by `-Wextra`: `warning: missing initializer for member 'after::Window::width'`), but it is a warning and is often suppressed because `T x{}` is a legitimate idiom for zero-initialization.

The same happens whenever someone adds a member in the middle of a struct that is initialized positionally across a codebase, or a library you do not control changes a public aggregate's layout. Nothing is undefined; the program does something defined that nobody intended. No sanitizer helps, so it must be caught in review or with warnings.

## The fix (`good.cpp`)

C++20 designated initializers (`{.border = 2, .height = 600, .width = 800}`) name the members. The designators must appear in declaration order (g++ rejects out-of-order designators, `error: designator order for field 'Window::border' does not match declaration order`; clang++ only emits `-Wreorder-init-list`), so a reorder produces a diagnostic rather than silently shifting values. Earlier standards have no equivalent, so add a constructor or a factory function, or give distinct types to members that could be confused (for example `Width` and `Height` wrappers). If you do not need aggregate behavior, a user-provided constructor makes the parameter order explicit at the declaration instead.

## Rust (`good.rs`)

Rust struct literals always name their fields and accept them in any order; there is no positional form (`Window { 800, 600, 2 }` is a syntax error) and every field must be supplied (`E0063: missing field`).
