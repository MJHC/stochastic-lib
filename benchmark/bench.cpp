#include <benchmark/benchmark.h>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

static std::vector<int> make_random(int size){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist{};
        auto vec = std::vector<int>{size};
        for(int i = 0; i < size; i++)
            vec.emplace_back(dist(gen));
        return vec;
}

static void bench_bench(benchmark::State& state){
    const auto n1 = state.range(0);
    for (auto _ : state){
        state.PauseTiming();
        auto vec = make_random(n1);
        state.ResumeTiming();
        std::sort(vec.begin(), vec.end());
        benchmark::DoNotOptimize(vec.data());
        benchmark::ClobberMemory();
    }
}

BENCHMARK(bench_bench)->Arg(100'000);