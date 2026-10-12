# 020 — Incorrect `std::forward` usage

`std::forward<T>(x)` is a conditional cast: it yields an lvalue reference when `T` is an lvalue-reference type and an rvalue reference otherwise. The two ways to go wrong are using it more than once and giving it the wrong `T`.

| Case | Mistake |
| --- | --- |
| `01-forward-twice` | A second use of a forwarded name after an rvalue was already forwarded away. |
| `02-wrong-template-argument` | `std::forward<T>` with the class's `T` instead of the forwarding reference's own `U`. |
