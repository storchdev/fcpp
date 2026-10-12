# 006 — Implicit conversion chains

An implicit conversion sequence is: at most one standard conversion, then at most one user-defined conversion (a converting constructor or conversion function), then at most one standard conversion ([over.best.ics]). Overload resolution ranks standard sequences better than user-defined ones, regardless of how "natural" the user-defined one looks.

| Case | Consequence of the rule |
| --- | --- |
| `01-standard-beats-user-defined` | a `const char*` argument picks `log(bool)` over `log(const std::string&)`. |
| `02-one-user-defined-conversion` | a chain of two converting constructors is not attempted at all, so the call is ill-formed. |
