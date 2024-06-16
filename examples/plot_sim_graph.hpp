#ifndef PLOT_SIM_GRAPH_HPP
#define PLOT_SIM_GRAPH_HPP
#include "stochastic_lib.hpp"
#include "example_sim.hpp"

#include <vector>
#include <fstream>

void plot_and_graph_sim(stochastic::Vessel& v, stochastic::Simulator& sim, std::string plot_title,
                        std::string plot_file, std::string dot_file, double endtime)
{
    std::vector<double> time{};
    std::vector<std::vector<int>> ts{};

    auto keys = v.symbols().keys(true);
    ts.reserve(keys.size());

    for (int i = 0; i < keys.size(); i++) {
        ts.emplace_back(std::vector<int>{});
    }
    std::cout << "Simulating...\n";
    for (const auto& series : sim.simulate(endtime)) {
        time.push_back(series.first);
        auto values = series.second->values(true);
        for (int i = 0; i < ts.size(); i++)
            ts[i].push_back(values[i]);
    }

    std::cout << "Plotting...\n";
    stochastic::plot_time_series(plot_title, plot_file, time, keys, ts);

    std::cout << "Dotting...\n";
    std::ofstream f2{dot_file};
    if (!f2.is_open())
        throw std::runtime_error("Dot File is not open");
    stochastic::write_dot_graph(f2, v.networkGraph());
    f2.close();
    std::cout << "Done!\n";
}

#endif  // !PLOT_SIM_GRAPH_HPP