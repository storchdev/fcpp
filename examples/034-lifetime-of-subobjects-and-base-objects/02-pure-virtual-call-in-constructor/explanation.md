# 034.02 — Lifetime of subobjects and base objects: a pure virtual call in a constructor

## Why the bad code is wrong (`bad.cpp`)

During `Base::Base()` the dynamic type is `Base`, so `init()` → `hook()` resolves to `Base::hook`, which is pure virtual and has no definition. The call is indirect (through `init()`), so the compiler does not see it and the program links. At run time g++ 16.2.1 and clang++ 23.1.1 (libstdc++, `-std=c++17`) print `pure virtual method called` and `terminate called without an active exception`, exiting with status 134 (abort). Calling a pure virtual function from a constructor, directly or indirectly, is undefined behavior; the abort is what these runtimes do, not a guarantee. A *direct* call `hook();` in the constructor is diagnosed (scratch program): g++ warns `pure virtual ‘virtual void Base::hook()’ called from constructor` and then fails to link with `undefined reference to `Base::hook()'`; clang++ warns `call to pure virtual member function 'hook' has undefined behavior; overrides of 'hook' in subclasses are not available in the constructor of 'Base' [-Wcall-to-pure-virtual-from-ctor-dtor]`.

Detection: clang-tidy `clang-analyzer-cplusplus.PureVirtualCall` reports `Call to pure virtual method 'Base::hook' during construction has undefined behavior` (verified on `bad.cpp`, which uses the indirect form). No `-Wall -Wextra` warning from either compiler, and no sanitizer applies.

## The fix (`good.cpp`)

Split construction from the virtual step: construct the object, then call `init()` once the derived part exists. A factory function can enforce that order, or pass the needed behavior into the base constructor as a parameter (a function object or a policy type) instead of a virtual hook.
