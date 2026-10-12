# 036 — Proxy references

`std::vector<bool>` packs bits, so `operator[]` returns a proxy object (`std::vector<bool>::reference`), not a `bool&`.

| Case | Consequence |
| --- | --- |
| `01-auto-copies-the-proxy` | `auto x = v[0]` copies the proxy, which still refers to the bit in the vector; later writes show through. |
| `02-cannot-bind-lvalue-reference` | `bool& r = v[0]` and `for (auto& b : v)` do not compile. |
