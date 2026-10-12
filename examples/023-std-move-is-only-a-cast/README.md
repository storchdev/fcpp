# 023 — `std::move` is only a cast

`std::move(x)` is a cast to an rvalue reference and performs no move. A move happens only if what receives the result has a move-taking overload that is selected. The two cases cover the receiver that cannot move and the type that cannot be moved.

| Case | Why nothing moves |
| --- | --- |
| `01-move-into-const-ref-or-int` | The receiver is a `const T&` parameter or a trivially copyable type; copying is all it can do. |
| `02-no-move-constructor` | A user-declared destructor suppresses the implicit move constructor, so `Packet(const Packet&)` is selected. |
