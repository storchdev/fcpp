# 112.02 — Dependent `typename` and `template` disambiguation: missing `template`

## Why the bad code is wrong (`bad.cpp`)

After a member access on a dependent object, `make` is not known to be a template, so `<` is parsed as a less-than operator: `m.make<int>()` reads as `(m.make < int) > ()`, which is meaningless. `m.template make<int>()` tells the parser that `make` is a template. g++ reports a warning "expected ‘template’ keyword before dependent template name [-Wmissing-template-keyword]" and then errors "expected primary-expression before ‘int’"; clang++ reports one error, "use 'template' keyword to treat 'make' as a dependent template name". The compile fails on both.

The syntax looks odd enough that people try to work around it rather than add `template`. Detection is the compile error.

## The fix (`good.cpp`)

Write `m.template make<int>()`. The fixed program prints `0`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

