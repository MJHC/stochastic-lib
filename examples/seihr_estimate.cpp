#include "stochastic_lib.hpp"
#include "example_sim.hpp"
#include <iostream>

#define ENDTIME 100
#define NDK     5'822'763
#define NNJ     589'755

/*
7. Implement a generic support for (any) user-supplied state observer function object or provide a lazy trajectory
generation interface (coroutine). The observer itself should be supplied by the user/test and not be part of
the library. To demonstrate the generic support, estimate the peak of hospitalized agents in Covid-19 example
without storing entire trajectory data. Record the peak hospitalization values for population sizes of NNJ and
NDK.
*/

int main()
{
    auto seihr = stochastic::seihr(10000);

    stochastic::Simulator sim{seihr, 5};

    std::vector<int> v{};

    for (const auto& series : sim.simulate_n_queue(ENDTIME, 100)) {
        v.push_back(series.second.second->get("H"));
    }

    std::cout << "10000 over 100 simulations (H peak): "
              << static_cast<double>(std::accumulate(v.begin(), v.end(), 0)) / v.size() << "\n";

    v.clear();

    auto nnj = stochastic::seihr(NNJ);
    stochastic::Simulator nnjsim{nnj, 5};
    for (const auto& series : nnjsim.simulate(ENDTIME)) {
        v.push_back(series.second->get("H"));
    }
    std::cout << "NNJ (H peak): " << *std::max_element(v.begin(), v.end()) << "\n";

    v.clear();
    auto ndk = stochastic::seihr(NDK);
    stochastic::Simulator ndksim{ndk, 5};
    for (const auto& series : ndksim.simulate(ENDTIME)) {
        v.push_back(series.second->get("H"));
    }
    std::cout << "NDK (H peak): " << *std::max_element(v.begin(), v.end()) << "\n";

    return 0;
}