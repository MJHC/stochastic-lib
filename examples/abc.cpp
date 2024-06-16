#include "plot_sim_graph.hpp"

struct abc_val
{
    int a;
    int b;
    int c;
};

int main()
{
    std::vector<abc_val> abc_values = {{100, 0, 1}, {100, 0, 2}, {50, 50, 1}};

    for (int i = 0; i < abc_values.size(); i++) {
        const auto& e = abc_values[i];
        auto v = stochastic::abc(e.a, e.b, e.c);
        stochastic::Simulator sim{v};
        auto num = std::to_string(i + 1);

        plot_and_graph_sim(v, sim, "ABC" + num, "abc" + num + ".png", "abc" + num + ".dot", 2000);
    }

    return 0;
}