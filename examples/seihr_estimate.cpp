#include "stochastic_lib.hpp"
#include "example_sim.hpp"
#include <iostream>

#define ENDTIME 100
#define NDK     5'822'763
#define NNJ     589'755

int main()
{
    auto seihr = stochastic::seihr(10000);

    stochastic::Simulator sim{seihr, 5};

    std::vector<int> v{};

    for (const auto& series : sim.simulate_n_queue(ENDTIME, 100)) {
        v.push_back(series.second.second->get("H"));
    }

    std::cout << "10000 over 100 simulations (H peak): " << *std::max_element(v.begin(), v.end()) << "\n";

    v.clear();
    seihr = stochastic::seihr(NNJ);
    for (const auto& series : sim.simulate(ENDTIME)) {
        v.push_back(series.second->get("H"));
    }
    std::cout << "NNJ (H peak): " << *std::max_element(v.begin(), v.end()) << "\n";

    v.clear();
    seihr = stochastic::seihr(NDK);
    for (const auto& series : sim.simulate(ENDTIME)) {
        v.push_back(series.second->get("H"));
    }
    std::cout << "NDK (H peak): " << *std::max_element(v.begin(), v.end()) << "\n";

    return 0;
}