#include <benchmark/benchmark.h>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

#include "stochastic_lib.hpp"
#include "example_sim.hpp"

#define ENDTIME 100

static void bench_simulation_n_queue(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming();

        auto seihr = stochastic::seihr(state.range(0));
        stochastic::Simulator sim{seihr};
        state.ResumeTiming();

        for (const auto& serie : sim.simulate_n_queue(ENDTIME, 100)) {
            continue;
        }
        benchmark::ClobberMemory();
    }
}

static void bench_simulation_n(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming();

        auto seihr = stochastic::seihr(state.range(0));
        stochastic::Simulator sim{seihr};
        state.ResumeTiming();

        for (const auto& serie : sim.simulate_n(ENDTIME, 100)) {
            continue;
        }
        benchmark::ClobberMemory();
    }
}

static void bench_simulation_n_cpu_cores(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming();

        auto seihr = stochastic::seihr(state.range(0));
        stochastic::Simulator sim{seihr};
        state.ResumeTiming();

        for (const auto& serie : sim.simulate_n_cpu_cores(ENDTIME, 100)) {
            continue;
        }
        benchmark::ClobberMemory();
    }
}

static void bench_simulation_single_core(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming();

        auto seihr = stochastic::seihr(state.range(0));
        stochastic::Simulator sim{seihr};
        state.ResumeTiming();

        for (int i = 0; i < state.range(1); i++) {
            for (const auto& serie : sim.simulate(ENDTIME)) {
                continue;
            }
        }

        benchmark::ClobberMemory();
    }
}

BENCHMARK(bench_simulation_n_queue)->Arg(10'000)->Name("100 Multi Sim Queue 10'000");
BENCHMARK(bench_simulation_n_cpu_cores)->Arg(10'000)->Name("100 Multi Sim CPU Cores 10'000");
BENCHMARK(bench_simulation_n)->Arg(10'000)->Name("100 Multi Sim 10'000");
BENCHMARK(bench_simulation_single_core)->Args({10'000, 100})->Name("100 Single Core Sim 10'000");
BENCHMARK(bench_simulation_single_core)->Args({10'000, 1})->Name("1 Single Core Sim 10'000");