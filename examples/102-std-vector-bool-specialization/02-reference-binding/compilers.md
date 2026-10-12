# 102.02 — `std::vector<bool>` specialization: no `bool&`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** Both reject `bad.cpp` at `-O0` and `-O2`:

| | g++ | clang++ |
| --- | --- | --- |
| Error | "cannot bind non-const lvalue reference of type ‘std::_Bit_reference&’ to an rvalue of type ‘std::_Bit_iterator::reference’" | "non-const lvalue reference to type 'reference' (aka '_Bit_reference') cannot bind to a temporary of type 'reference' (aka '_Bit_reference')" |
