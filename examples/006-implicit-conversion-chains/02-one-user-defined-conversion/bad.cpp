// std: c++17
// expect: compile-error
// An implicit conversion sequence may contain at most one user-defined conversion.
#include <cstdio>

struct Meters {
    Meters(double v) : value(v) {}          // converting constructor: double -> Meters
    double value;
};

struct Distance {
    Distance(Meters m) : meters(m) {}       // converting constructor: Meters -> Distance
    Meters meters;
};

void travel(Distance d) { std::printf("%.1f m\n", d.meters.value); }

int main() {
    travel(Meters(5.0));   // OK: one user-defined conversion (Meters -> Distance)
    travel(5.0);           // error: would need double -> Meters -> Distance (two user-defined conversions)
}
