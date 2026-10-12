# 022.01 — Reference-qualified member functions: mixing qualified and unqualified

## Why the bad code is wrong (`bad.cpp`)

`const std::string& name() const` has no ref-qualifier and `std::string name() &&` has one. They have the same parameter list, and the language does not allow overloading between a ref-qualified and an unqualified member with the same parameters, even though they differ in `const`. The program is ill-formed and both compilers say so on the second declaration (`-std=c++17`):

- g++ 16.2.1: `error: ‘std::string Person::name() &&’ cannot be overloaded with ‘const std::string& Person::name() const’`
- clang++ 23.1.1: `error: cannot overload a member function with ref-qualifier '&&' with a member function without a ref-qualifier`

The attempt is natural: "return a reference normally, but move out when the object is a temporary". The unqualified overload was written first, and the `&&` overload was added later as an optimization.

## The fix (`good.cpp`)

Qualify every overload: `const std::string& name() const&` and `std::string name() &&`. An lvalue (or const rvalue) picks `const&`, a non-const rvalue picks `&&`; `good.cpp` shows both. Detection is the compile error on both compilers.
