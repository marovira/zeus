#define ZEUS_ASSERT_IMPL
#define ZEUS_ENABLE_TESTING_MACROS
#include <zeus/assert.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("[assert] - assert macro", "[zeus]")
{
    constexpr auto test_val{0};
    SECTION("Valid assertion")
    {
        REQUIRE_NOTHROW(ASSERT(test_val == 0));
    }

    SECTION("Invalid assertion")
    {
        REQUIRE_THROWS(ASSERT(test_val == 1));
    }
}
