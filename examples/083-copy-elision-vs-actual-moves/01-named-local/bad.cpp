// expect: compile-error
// std: c++17
// Only prvalues get guaranteed elision; returning a named local still needs an accessible move or copy constructor.
// g++:     error: use of deleted function 'Pinned::Pinned(Pinned&&)'
// clang++: error: call to deleted constructor of 'Pinned'
struct Pinned {
    Pinned() = default;
    Pinned(Pinned&&) = delete;
};

Pinned make() {
    Pinned p;
    return p;
}

int main() { Pinned x = make(); (void)x; }
