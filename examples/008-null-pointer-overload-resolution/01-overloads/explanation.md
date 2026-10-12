# 008.01 — Null pointer overload resolution: `0`, `NULL`, `nullptr`

## Why the bad code is wrong (`bad.cpp`)

Before C++11 the only null pointer was "an integral constant expression that evaluates to zero". That is still true: `0` is a literal of type `int` that can also be converted to any pointer ([conv.ptr]). In overload resolution it is an `int` first. `NULL` is an implementation-defined null pointer constant (see the cppreference `NULL` page); in C++ it must be an integer literal or prvalue of type `std::nullptr_t`. It cannot be `(void*)0`. On this platform (g++ 16.2 and clang++ 23.1 with libstdc++) it is an integer of type `long`.

Observed results:

| Call | Overloads | Result |
| --- | --- | --- |
| `report(0)` | `int` / `const char*` | `report(int)`. Exact match beats a conversion. |
| `report(NULL)` | `int` / `const char*` | **error: ambiguous** (both compilers). `long` to `int` and null-to-pointer are both conversions. |
| `assign(NULL)` | `long` / `const char*` | `assign(long)`. Exact match on `long`. g++ adds `warning: passing NULL to non-pointer argument 1 of 'void assign(long int)' [-Wconversion-null]`; clang++ printed no warning with `-Wall -Wextra`. |
| `assign(0)` | `long` / `const char*` | error: ambiguous (both compilers). |
| `assign(nullptr)` | any | the `const char*` overload, since `std::nullptr_t` converts to pointers and not to integers. |

So the same spelling of "no pointer" gives an error in one overload set and silently selects an integer function in another, and the result depends on how the standard library defines `NULL`. None of this is undefined behavior; it is a trap in what the compiler calls.

## The fix (`good.cpp`)

Write `nullptr` everywhere. It has a dedicated type, `std::nullptr_t`, which converts to every pointer and pointer-to-member type and to `bool` (only in direct-initialization), and never to an integer. To find leftovers, `-Wzero-as-null-pointer-constant` (g++ and clang++) flags a literal `0` used as a null pointer but, in my check, not `NULL`; clang-tidy's `modernize-use-nullptr` flags both in pointer contexts (`const char* p = NULL;`) and can rewrite them. Neither flags `assign(NULL)` above, because there `NULL` really is used as an integer; g++'s `-Wconversion-null` is the one that does.
