#include <zeus/float.hpp>

#include <catch2/catch_template_test_macros.hpp>
#include <cmath>

template<typename T>
inline constexpr T epsilon()
{
    return static_cast<T>(0.00001);
}

TEMPLATE_TEST_CASE("[float] - are_equal", "[zeus]", float, double)
{
    using zeus::are_equal;

    auto d1{static_cast<TestType>(0.2)};
    auto d2 = static_cast<TestType>(1 / std::sqrt(5) / std::sqrt(5));

    SECTION("Default epsilon")
    {
        REQUIRE(are_equal(d1, d2));
    }

    SECTION("Custom epsilon")
    {
        REQUIRE(are_equal<TestType, epsilon>(d1, d2));
    }
}

TEMPLATE_TEST_CASE("[float] - is_zero", "[zeus]", float, double)
{
    using zeus::is_zero;

    auto d1 = static_cast<TestType>(1.0 - (std::sqrt(5.0) / std::sqrt(5.0)));

    SECTION("Default epsilon")
    {
        REQUIRE(is_zero(d1));
    }

    SECTION("Custom epsilon")
    {
        REQUIRE(is_zero<TestType, epsilon>(d1));
    }
}

TEMPLATE_TEST_CASE("[float] - geq", "[zeus]", float, double)
{
    using zeus::geq;

    auto d1{static_cast<TestType>(0.2)};
    auto d2 = static_cast<TestType>(1 / std::sqrt(5) / std::sqrt(5));
    auto d3 = static_cast<TestType>(1.0 + d2);

    SECTION("Default epsilon")
    {
        REQUIRE(geq(d1, d2));
        REQUIRE(geq(d3, d2));
    }

    SECTION("Custom epsilon")
    {
        REQUIRE(geq<TestType, epsilon>(d1, d2));
        REQUIRE(geq<TestType, epsilon>(d3, d2));
    }
}

TEMPLATE_TEST_CASE("[float] - leq", "[zeus]", float, double)
{
    using zeus::leq;

    auto d1{static_cast<TestType>(0.2)};
    auto d2 = static_cast<TestType>(1 / std::sqrt(5) / std::sqrt(5));
    auto d3 = static_cast<TestType>(1.0 + d2);

    SECTION("Default epsilon")
    {
        REQUIRE(leq(d1, d2));
        REQUIRE(leq(d2, d3));
    }

    SECTION("Custom epsilon")
    {
        REQUIRE(leq<TestType, epsilon>(d1, d2));
        REQUIRE(leq<TestType, epsilon>(d2, d3));
    }
}
