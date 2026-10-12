// std: c++17
// Make the chain explicit, or give the outer type a constructor that takes what callers really have.
#include <cstdio>

struct Meters {
    explicit Meters(double v) : value(v) {}
    double value;
};

struct Distance {
    explicit Distance(Meters m) : meters(m) {}
    explicit Distance(double v) : meters(v) {}   // the conversion callers actually want, spelled out once
    Meters meters;
};

void travel(Distance d) { std::printf("%.1f m\n", d.meters.value); }

int main() {
    travel(Distance(Meters(5.0)));
    travel(Distance{5.0});
}
