#include "Simulator.hpp"

using namespace stochastic;

namespace stochastic
{
    // 4. Implement the stochastic simulation (Alg. 1) of the system using the reaction rules.
    double Simulator::_compute_delay(const ReactionRule& rule, std::shared_ptr<SymbolTable<std::string, int>>& state)
    {
        thread_local std::mt19937 gen{seed == 0 ? rd() : seed};

        std::vector<int> values{};
        values.reserve(rule.reactants.size());

        auto get_value_pred = [&state](const Symbol& s) { return state->get(s.name()); };
        std::transform(rule.reactants.begin(), rule.reactants.end(), std::back_inserter(values), get_value_pred);

        auto product = std::accumulate(values.begin(), values.end(), 1, std::multiplies<int>{});

        std::exponential_distribution dist{rule.delay * product};
        return dist(gen);
    }

    void Simulator::_react(const ReactionRule& rule, std::shared_ptr<SymbolTable<std::string, int>> state) const
    {
        auto is_empty_pred = [&state](const Symbol& s) { return state->get(s.name()) == 0; };
        auto is_empty = std::any_of(rule.reactants.begin(), rule.reactants.end(), is_empty_pred);

        if (is_empty)
            return;

        for (const auto& s : rule.reactants)
            if (std::find(rule.products.begin(), rule.products.end(), s) == rule.products.end())
                state->get(s.name())--;
        for (const auto& s : rule.products)
            if (std::find(rule.reactants.begin(), rule.reactants.end(), s) == rule.reactants.end())
                state->get(s.name())++;
    }

    /*
    7. Implement a generic support for (any) user-supplied state observer function object or provide a lazy trajectory
        generation interface (coroutine). The observer itself should be supplied by the user/test and not be part of
        the library. To demonstrate the generic support, estimate the peak of hospitalized agents in Covid-19 example
        without storing entire trajectory data. Record the peak hospitalization values for population sizes of NNJ and
        NDK.
    */
    std::generator<const time_series_t> Simulator::simulate(double endtime)
    {
        const auto& rules = vessel.reactionRules();
        auto time = 0.0;
        auto state_ptr = std::make_shared<SymbolTable<std::string, int>>(vessel.symbols());

        co_yield std::make_pair(time, state_ptr);

        while (time <= endtime) {
            std::vector<double> delays{};
            delays.reserve(rules.size());

            auto compute_delay = [&state_ptr, this](const ReactionRule& r) { return _compute_delay(r, state_ptr); };
            std::transform(rules.begin(), rules.end(), std::back_inserter(delays), compute_delay);

            auto it = std::min_element(delays.begin(), delays.end());
            if (it == delays.end())
                continue;

            auto i = std::distance(delays.begin(), it);
            time += *it;

            _react(rules[i], state_ptr);
            co_yield std::make_pair(time, state_ptr);
        }
    }

    /*
    8. Implement support for multiple computer cores by parallelizing the computation of several simulations at the
    same time. Estimate the likely (average) value of the hospitalized peak over 100 simulations.
    */
    std::generator<const n_time_series_t> Simulator::simulate_n_queue(double endtime, int sim_count)
    {
        std::vector<std::future<void>> futures{};
        ThreadQueue<n_time_series_t> q{};

        auto job = [this, &q, endtime](int sim_id) {
            for (const auto& t : simulate(endtime))
                q.add(std::make_pair(sim_id, t));
        };

        for (int i = 0; i < sim_count; i++) {
            futures.emplace_back(std::async(std::launch::async, job, i));
        }

        auto is_finished = [](const std::future<void>& f) {
            return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
        };
        while (true) {
            if (!q.empty())
                co_yield q.get();
            else if (std::all_of(futures.begin(), futures.end(), is_finished))
                break;
        }
    }

    const std::vector<n_time_series_t> Simulator::simulate_n(double endtime, int sim_count)
    {
        std::vector<std::future<std::vector<n_time_series_t>>> futures{};

        auto job = [this, endtime](int sim_id) {
            std::vector<n_time_series_t> v{};
            for (const auto& t : simulate(endtime))
                v.push_back(std::make_pair(sim_id, t));
            return v;
        };

        for (int i = 0; i < sim_count; i++) {
            futures.emplace_back(std::async(std::launch::async, job, i));
        }

        std::vector<n_time_series_t> rv{};
        for (auto& f : futures) {
            auto res = f.get();
            rv.insert(rv.end(), res.begin(), res.end());
        }
        return rv;
    }

    const std::vector<n_time_series_t> Simulator::simulate_n_cpu_cores(double endtime, int sim_count)
    {
        std::vector<std::future<std::vector<n_time_series_t>>> futures{};
        unsigned int n = std::thread::hardware_concurrency();

        int sims_per_job = sim_count / n;

        auto job = [this, endtime, sims_per_job](int sim_id) {
            std::vector<n_time_series_t> v{};
            for (int i = 0; i < sims_per_job; i++) {
                for (const auto& t : simulate(endtime))
                    v.push_back(std::make_pair(sim_id + i, t));
            }
            return v;
        };

        for (int i = 0; i < sim_count; i += sims_per_job) {
            futures.emplace_back(std::async(std::launch::async, job, i));
        }

        std::vector<n_time_series_t> rv{};
        for (auto& f : futures) {
            auto res = f.get();
            rv.insert(rv.end(), res.begin(), res.end());
        }
        return rv;
    }

}  // namespace stochastic
