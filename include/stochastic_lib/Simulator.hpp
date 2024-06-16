#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP
#include <generator>
#include <future>
#include <vector>
#include <random>
#include <algorithm>

#include "Vessel.hpp"
#include "SymbolTable.hpp"
#include "ThreadQueue.hpp"

namespace stochastic
{
    using time_series_t = std::pair<double, std::shared_ptr<SymbolTable<std::string, int>>>;
    using n_time_series_t = std::pair<int, time_series_t>;
    class Simulator
    {
    private:
        Vessel vessel;
        std::random_device rd{};
        unsigned int seed = 0;

        double _compute_delay(const ReactionRule& rule, std::shared_ptr<SymbolTable<std::string, int>>& state);

        void _react(const ReactionRule& rule, std::shared_ptr<SymbolTable<std::string, int>> state) const;

    public:
        Simulator(Vessel& vessel): vessel{vessel} {}
        Simulator(Vessel& vessel, unsigned int seed): vessel{vessel}, seed{seed} {}

        std::generator<const time_series_t> simulate(double endtime);
        std::generator<const n_time_series_t> simulate_n_queue(double endtime, int sim_count);
        const std::vector<n_time_series_t> simulate_n(double endtime, int sim_count);
        const std::vector<n_time_series_t> simulate_n_cpu_cores(double endtime, int sim_count);
    };
}  // namespace stochastic

#endif  // !SIMULATOR_HPP