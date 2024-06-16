add_library(stochastic_lib Vessel.cpp utils.cpp Simulator.cpp ReactionRuleBuilderVisitor.cpp ReactionRule.cpp Graph.cpp)

target_include_directories(stochastic_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/stochastic_lib)
target_link_libraries(stochastic_lib Python3::NumPy)

add_dependencies(build_src stochastic_lib)