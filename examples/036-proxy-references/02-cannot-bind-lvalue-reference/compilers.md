# 036.02 — Proxy references: no lvalue reference to the element: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** Both reject `for (auto& f : flags)` at line 8, with different text. g++: `cannot bind non-const lvalue reference of type 'std::_Bit_reference&' to an rvalue of type 'std::_Bit_iterator::reference'`. clang++: `non-const lvalue reference to type 'reference' (aka '_Bit_reference') cannot bind to a temporary of type 'reference' (aka '_Bit_reference')`.
