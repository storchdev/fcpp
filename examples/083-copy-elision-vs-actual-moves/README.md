# 083 — Copy elision vs. actual moves

| Case | What it shows |
| --- | --- |
| `01-named-local` | Guaranteed elision (C++17) covers prvalues only; returning a named local still needs an accessible move or copy constructor. |
| `02-two-locals` | NRVO is optional; with two candidate locals a move constructor runs, so side effects in it are observable. |
