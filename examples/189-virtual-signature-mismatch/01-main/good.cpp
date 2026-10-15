// std: c++11
#include <iostream>

struct Renderer {
    virtual ~Renderer() = default;
    virtual int render(int scale) const { return scale; }
};

struct DetailedRenderer : Renderer {
    int render(int scale) const override { return scale * 2; }
};

int main() {
    DetailedRenderer detailed;
    Renderer& renderer = detailed;
    std::cout << renderer.render(3) << '\n';
}
