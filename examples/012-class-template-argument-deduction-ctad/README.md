# 012 — Class template argument deduction (CTAD)

C++17 deduces class template arguments from constructor calls by synthesizing a set of *deduction guides* from the constructors (plus any user-written guides) and one extra *copy deduction candidate* ([over.match.class.deduct]). The result follows the argument types literally, so it can differ from what the writer had in mind.

| Case | What it shows |
| --- | --- |
| `01-copy-deduction` | `std::vector v{x}` where `x` is already a `std::vector<int>` is a copy, not a vector of vectors. |
| `02-string-literals` | string literals deduce as `const char*`, so `std::vector{"a", "b"}` is not a vector of strings (and `std::vector("a", "b")` is a different type again). |

Mental model: CTAD is "what type would a function template taking these arguments deduce?" Use it where that is obviously what you want, and write the type where the arguments are containers, literals, or braced lists.
