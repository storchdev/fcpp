# 022.02 — Reference-qualified member functions: an `&`-only member on a temporary: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** Both reject `make_builder().add("y")` at line 18, at both levels. g++: `passing 'Builder' as 'this' argument discards qualifiers [-fpermissive]`. clang++: `'this' argument to member function 'add' is an rvalue, but function has non-const lvalue ref-qualifier`.
