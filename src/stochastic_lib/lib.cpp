#include "lib.hpp"
#include <iostream>

int lib_function(){
    int res = add(5, 2);
    std::cout << res << std::endl;
    return res;
}