# 022.01 — Reference-qualified member functions: mixing qualified and unqualified: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** Both reject the program with one error at line 11, at both levels. g++: `'std::string Person::name() &&' cannot be overloaded with 'const std::string& Person::name() const'`. clang++: `cannot overload a member function with ref-qualifier '&&' with a member function without a ref-qualifier`.
