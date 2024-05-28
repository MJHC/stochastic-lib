#include <doctest/doctest.h>
#include "lib.hpp"

TEST_CASE("THIS IS A TEST"){
    CHECK(1 == 1);
    SUBCASE("THIS IS A SUBCASE"){
        CHECK(lib_function() == 7);
    }
}