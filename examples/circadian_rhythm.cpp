
#include "plot_sim_graph.hpp"

int main()
{
    auto cr = stochastic::circadian_rhythm();

    stochastic::Simulator sim{cr};
    plot_and_graph_sim(cr, sim, "Circadian Rhythm", "circadian_rhythm.png", "circadian_rhythm.dot", 100);
    return 0;
}