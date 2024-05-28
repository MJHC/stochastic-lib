add_library(stochastic_lib lib.cpp)
target_include_directories(stochastic_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/stochastic_lib)