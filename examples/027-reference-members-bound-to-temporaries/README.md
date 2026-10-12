# 027 — Reference members bound to temporaries

Whether a temporary bound to a reference *member* is extended depends on the initialization syntax. Both cases dangle; the contrast with the working syntax is the lesson.

| Case | Context |
| --- | --- |
| `01-constructor-parameter` | `Logger(const std::string&) : prefix_(prefix)`: the parameter's temporary dies when the constructor's full-expression ends. |
| `02-parenthesized-aggregate-init` | `Name(std::string(...))` in C++20: not extended, unlike `Name{std::string(...)}`. |

(For `new Name{...}` see entry 026.)
