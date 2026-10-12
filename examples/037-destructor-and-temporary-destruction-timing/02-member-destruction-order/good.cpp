// std: c++17
// Declare dependencies first: the user (`stage`) is then destroyed before the thing it uses (`stats`).
#include <vector>

struct Stats { std::vector<int> samples{1, 2, 3}; };

struct Stage {
    Stats& stats;
    explicit Stage(Stats& s) : stats(s) {}
    ~Stage() { stats.samples.push_back(0); }
};

struct Pipeline {
    Stats stats;       // constructed first, destroyed last
    Stage stage;
    Pipeline() : stage(stats) {}
};

int main() {
    Pipeline p;
}
