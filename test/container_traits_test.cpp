#include <zeus/container_traits.hpp>

#include <catch2/catch_test_macros.hpp>

#include <array>
#include <list>
#include <string>
#include <vector>

TEST_CASE("[container_traits] - ContiguousContainer", "[zeus]")
{
    STATIC_REQUIRE(zeus::ContiguousContainer<std::vector<int>>);
    STATIC_REQUIRE(zeus::ContiguousContainer<std::array<int, 3>>);
    STATIC_REQUIRE(zeus::ContiguousContainer<std::basic_string<char>>);
    STATIC_REQUIRE_FALSE(zeus::ContiguousContainer<std::list<int>>);
}
