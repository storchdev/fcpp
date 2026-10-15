# 189 — Virtual signature mismatch

## Why the bad code is wrong (`bad.cpp`)

Overriding a virtual member requires a matching function signature. `Renderer::render` takes `int`, while `DetailedRenderer::render` takes `double`. The latter declares a different member and hides the base name for lookup through `DetailedRenderer`; it does not replace the virtual function in calls through `Renderer&`.

The call through `renderer` therefore prints `3`, from the base implementation, instead of the derived implementation's `6`. Both compilers reported `-Woverloaded-virtual` in the verified build. A reviewer should compare the complete signatures, including parameters and cv/ref qualifiers, when an override is intended.

## The fix (`good.cpp`)

Give the derived function the matching `int` parameter and mark it `override`. The specifier makes a future signature mismatch a compile-time error. If both overloads are wanted, they need distinct declarations, but the virtual override must still match the base function.

## Rust (no `good.rs`)

No Rust equivalent is provided for this C++ virtual member lookup case.
