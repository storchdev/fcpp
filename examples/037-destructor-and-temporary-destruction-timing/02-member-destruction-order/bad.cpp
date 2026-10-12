// std: c++17
// sanitize: address
// Members are destroyed in reverse declaration order; `stage` is destroyed after `stats`, but its destructor uses it.
#include <vector>

struct Stats { std::vector<int> samples{1, 2, 3}; };

struct Stage {
    Stats& stats;
    explicit Stage(Stats& s) : stats(s) {}
    ~Stage() { stats.samples.push_back(0); }   // flush on shutdown: stats is already destroyed
};

struct Pipeline {
    Stage stage;       // declared first  -> destroyed last
    Stats stats;       // declared second -> destroyed first
    Pipeline() : stage(stats) {}
};

int main() {
    Pipeline p;
}
