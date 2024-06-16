add_executable(test_test test.cpp)
target_link_libraries(test_test PRIVATE stochastic_lib)
target_link_libraries(test_test PRIVATE doctest::doctest_with_main)

target_include_directories(stochastic_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/stochastic_lib)
add_test(NAME test_test COMMAND test_test)

add_dependencies(build_test test_test)