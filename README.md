# Stochastic Simulation Library

simulation library for stochastic simulations so you can stimulate your urges to look at stochastic simulations

# Structure

- In `examples` there are examples of the use of this library on a simple A + C - Lambda -> C + B rule and the Circadian Rythm aswell as seihr covid 19.
running these examples will generate a dot file of the network, and a graph, these will be located in the same folder as the executables. 
- In `benchmark` you can find a benchmark cpp file that bench marks different multithreaded implementations of the simulation aswell as a single threaded.
- In `test` there are tests for most of the classes and functionality of the library.

# Build instructions

ensure that `matplotlibcpp.h` is in `libs\matplotlib\include`. If not you can get it from https://github.com/Cryoris/matplotlib-cpp

You also need to have minimum python 3.10, numpy and eigen3. 

You also need gcc 14.xxx, or any other compiler supporting c++ 23. 

