function(add_custom_executable target source)
    add_executable(${target} ${source})
    target_link_libraries(${target} PRIVATE stochastic_lib)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/stochastic_lib)
endfunction()

# Demonstrate the application of the library on the three examples (shown in Fig. 1, 2, 3).
add_custom_executable(abc abc.cpp)
add_custom_executable(seihr seihr.cpp)
add_custom_executable(seihr_estimate seihr_estimate.cpp)
add_custom_executable(circadian_rhythm circadian_rhythm.cpp)

add_dependencies(build_examples abc seihr circadian_rhythm)