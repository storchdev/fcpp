// std: c++17
// sanitize: undefined
// typeid/dynamic_cast on a polymorphic object whose construction has not reached that subobject is UB.
#include <cstdio>
#include <typeinfo>

struct Observer {
    virtual ~Observer() = default;
};
struct Registrar {
    explicit Registrar(Observer* o);
    virtual ~Registrar() = default;
};
struct Widget : Registrar, Observer {          // Registrar is constructed first, Observer second
    Widget() : Registrar(this) {}              // this -> Observer*: that base has no vptr yet
};

Registrar::Registrar(Observer* o) {
    std::printf("registering %s\n", typeid(*o).name());   // UB: Observer is not constructed
}

int main() {
    Widget w;
}
