#include "plot_sim_graph.hpp"

int main()
{
    auto seihr = stochastic::seihr(10000);

    stochastic::Simulator sim{seihr, 5};
    plot_and_graph_sim(seihr, sim, "Seihr Covid-19", "seihr.png", "seihr.dot", 100);
    return 0;
}