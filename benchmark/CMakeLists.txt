add_executable(bench bench.cpp)
target_link_libraries(bench PRIVATE benchmark::benchmark_main)
target_link_libraries(bench PRIVATE stochastic_lib)
add_test(NAME bench COMMAND bench)
target_include_directories(stochastic_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/stochastic_lib)

# target_link_libraries(test stochastic_lib)
add_dependencies(build_benchmark bench)