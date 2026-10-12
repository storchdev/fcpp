# 073 — Pure virtual calls in object lifetime transitions

## Why the bad code is wrong (`bad.cpp`)

Entry 072 showed that a virtual call in a constructor resolves to the constructor's own class. If that final overrider is a pure virtual function, there is nothing to call. Calling a pure virtual function through the dynamic type of an object under construction has nothing to dispatch to, and clang-tidy's analyzer reports it as undefined behavior (see below). Here `Base()` calls `init()`, which calls `run()` on an object whose dynamic type is `Base`, and `Base::run` is pure.

A direct call is often diagnosed by the compiler, which is why the example hides it behind `init()`. The indirect call compiles without any warning from either compiler under `-Wall -Wextra`. At run time both programs aborted with `pure virtual method called`, followed by `terminate called without an active exception` and a core dump, at `-O0` and `-O2`. That is what this implementation does; the standard permits anything.

`clang-tidy` finds it: `clang-analyzer-cplusplus.PureVirtualCall` reported "Call to pure virtual method 'Base::run' during construction has undefined behavior".

## The fix (`good.cpp`)

Do not call virtual functions (pure or not) from constructors and destructors. Run the extra initialization step after construction, from the owner or a factory, when the dynamic type is complete.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
