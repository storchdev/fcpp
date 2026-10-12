// std: c++17
struct Pinned {
    Pinned() = default;
    Pinned(Pinned&&) = delete;
};

Pinned make() {
    return Pinned();                           // prvalue: guaranteed elision, no move constructor needed
}

int main() {
    Pinned x = make();
    (void)x;
}
