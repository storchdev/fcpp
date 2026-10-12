# 027.02 — Reference members bound to temporaries: parenthesized aggregate initialization

## Why the bad code is wrong (`bad.cpp`)

`Name braces{std::string("…")};` is aggregate initialization with a braced list: the temporary bound to the reference member is extended to the lifetime of `braces`. `Name parens(std::string("…"));` is C++20 parenthesized aggregate initialization, which is allowed to initialize an aggregate with a parenthesized list — but it does not extend the temporary. In my runs both compilers (g++ 16.2.1 and clang++ 23.1.1, `-std=c++20 -O1`) read `braces.text` fine and reported `stack-use-after-scope` for the read through `parens.text`.

The two forms differ only in the bracket type, which is easy to miss in review.

Detection: clang++ 23.1.1 warns under `-Wall -Wextra`: `warning: temporary whose address is used as value of local variable 'parens' will be destroyed at the end of the full-expression [-Wdangling]`. g++ did not warn in my run.

## The fix (`good.cpp`)

Make the member a value (`std::string text;`). For a reference member, initialize from a named object, not a temporary.
