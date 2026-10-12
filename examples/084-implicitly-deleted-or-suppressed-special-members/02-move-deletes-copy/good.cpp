// std: c++17
struct Handle {
    int fd = -1;
    Handle() = default;
    Handle(Handle&& o) noexcept : fd(o.fd) { o.fd = -1; }
    Handle(const Handle&) = default;           // opt back in (a real fd wrapper would dup() here)
};

int main() {
    Handle a;
    Handle b = a;
    (void)b;
}
