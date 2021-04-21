#include <zeus/type_traits.hpp>

#include <catch2/catch.hpp>
#include <tuple>

TEST_CASE("[type_traits] - Contains", "[zeus]")
{
    SECTION("Contains type")
    {
        STATIC_REQUIRE(zeus::Contains<int, int, long, float>::value);
    }

    SECTION("Doesn't contain type")
    {
        STATIC_REQUIRE_FALSE(zeus::Contains<char, int, long, float>::value);
    }
}
