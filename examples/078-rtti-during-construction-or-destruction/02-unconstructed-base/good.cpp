// std: c++17
#include <cstdio>
#include <typeinfo>

struct Observer {
    virtual ~Observer() = default;
};
struct Registrar {
    virtual ~Registrar() = default;
    void add(Observer* o) { std::printf("registering %s\n", typeid(*o).name()); }
};
struct Widget : Registrar, Observer {
    Widget() = default;
    void start() { add(this); }                // register once the whole object exists
};

int main() {
    Widget w;
    w.start();
}
