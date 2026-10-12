// expect: compile-error
// std: c++17
// Declaring a move constructor makes the implicit copy constructor deleted.
// g++:     error: use of deleted function 'Handle::Handle(const Handle&)'
// clang++: error: call to implicitly-deleted copy constructor of 'Handle'
struct Handle {
    int fd = -1;
    Handle() = default;
    Handle(Handle&& o) noexcept : fd(o.fd) { o.fd = -1; }
};

int main() {
    Handle a;
    Handle b = a;
    (void)b;
}
