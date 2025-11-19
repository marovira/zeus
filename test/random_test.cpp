#include <zeus/random.hpp>

#include <catch2/catch_get_random_seed.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

TEMPLATE_TEST_CASE("[Random] - get_Random_in_range", "[zeus]", int, float, double)
{
    zeus::Random<TestType> rand{Catch::getSeed()};

    auto r = rand.get_random_in_range(TestType{0}, TestType{10});
    REQUIRE(r >= TestType{0});
    REQUIRE(r <= TestType{10});
}

TEMPLATE_TEST_CASE("[Random] get_Random_zero_to_max", "[zeus]", int, float, double)
{
    zeus::Random<TestType> rand{Catch::getSeed()};

    auto r = rand.get_random_zero_to_max();
    REQUIRE(r >= TestType{0});
}

TEMPLATE_TEST_CASE("[Random] get_Random_zero_to_one", "[zeus]", int, float, double)
{
    zeus::Random<TestType> rand{Catch::getSeed()};

    auto r = rand.get_random_zero_to_one();
    REQUIRE(r >= TestType{0});
    REQUIRE(r <= TestType{1});
}
