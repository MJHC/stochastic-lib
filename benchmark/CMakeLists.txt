add_executable(bench bench.cpp)
target_link_libraries(bench PRIVATE benchmark::benchmark_main)
add_test(NAME bench COMMAND bench)

#target_link_libraries(test stochastic_lib)
