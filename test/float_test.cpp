#include <zeus/float.hpp>

#include <catch2/catch.hpp>
#include <cmath>

template<typename T>
inline constexpr T epsilon()
{
    return static_cast<T>(0.00001);
}

TEST_CASE("[float] - are_equal: default epsilon", "[zeus]")
{
    using zeus::are_equal;

    double d1 = 0.2;
    double d2 = 1 / std::sqrt(5) / std::sqrt(5);
    REQUIRE(are_equal(d1, d2) == true);

    float f1 = 0.2f;
    float f2 = 1.0f / std::sqrt(5.0f) / std::sqrt(5.0f);
    REQUIRE(are_equal(f1, f2) == true);
}

TEST_CASE("[float] - are_equal: custom epsilon", "[zeus]")
{
    using zeus::are_equal;

    double d1 = 0.2;
    double d2 = 1 / std::sqrt(5) / std::sqrt(5);
    REQUIRE(are_equal<double, epsilon>(d1, d2) == true);

    float f1 = 0.2f;
    float f2 = 1.0f / std::sqrt(5.0f) / std::sqrt(5.0f);
    REQUIRE(are_equal<float, epsilon>(f1, f2) == true);
}

TEST_CASE("[float] - is_zero: default epsilon", "[zeus]")
{
    using zeus::is_zero;

    double d1 = 1.0 - (std::sqrt(5.0) / std::sqrt(5.0));
    REQUIRE(is_zero(d1) == true);

    float f1 = 1.0f - (std::sqrt(5.0f) / std::sqrt(5.0f));
    REQUIRE(is_zero(f1) == true);

    REQUIRE(is_zero<double, epsilon>(d1));
    REQUIRE(is_zero<float, epsilon>(f1));
}

TEST_CASE("[float] - is_zero: custom epsilon", "[zeus]")
{
    using zeus::is_zero;
    double d1 = 1.0 - (std::sqrt(5.0) / std::sqrt(5.0));
    REQUIRE(is_zero<double, epsilon>(d1));

    float f1 = 1.0f - (std::sqrt(5.0f) / std::sqrt(5.0f));
    REQUIRE(is_zero<float, epsilon>(f1));
}

TEST_CASE("[float] - geq: default epsilon", "[zeus]")
{
    using zeus::geq;

    double d1 = 0.2;
    double d2 = 1 / std::sqrt(5) / std::sqrt(5);
    double d3 = 1.0 + d2;

    REQUIRE(geq(d1, d2) == true);
    REQUIRE(geq(d3, d2) == true);

    float f1 = 0.2f;
    float f2 = 1 / std::sqrt(5.0f) / std::sqrt(5.0f);
    float f3 = 1.0f + f2;

    REQUIRE(geq(f1, f2) == true);
    REQUIRE(geq(f3, f2) == true);
}

TEST_CASE("[float] - geq: custom epsilon", "[zeus]")
{
    using zeus::geq;

    double d1 = 0.2;
    double d2 = 1 / std::sqrt(5) / std::sqrt(5);
    double d3 = 1.0 + d2;

    REQUIRE(geq<double, epsilon>(d1, d2) == true);
    REQUIRE(geq<double, epsilon>(d3, d2) == true);

    float f1 = 0.2f;
    float f2 = 1 / std::sqrt(5.0f) / std::sqrt(5.0f);
    float f3 = 1.0f + f2;

    REQUIRE(geq<float, epsilon>(f1, f2) == true);
    REQUIRE(geq<float, epsilon>(f3, f2) == true);
}

TEST_CASE("[float] - leq: default epsilon", "[zeus]")
{
    using zeus::leq;

    double d1 = 0.2;
    double d2 = 1 / std::sqrt(5) / std::sqrt(5);
    double d3 = 1.0 + d2;

    REQUIRE(leq(d1, d2) == true);
    REQUIRE(leq(d2, d3) == true);

    float f1 = 0.2f;
    float f2 = 1 / std::sqrt(5.0f) / std::sqrt(5.0f);
    float f3 = 1.0f + f2;

    REQUIRE(leq(f1, f2) == true);
    REQUIRE(leq(f2, f3) == true);
}

TEST_CASE("[float] - leq: custom epsilon", "[zeus]")
{
    using zeus::leq;

    double d1 = 0.2;
    double d2 = 1 / std::sqrt(5) / std::sqrt(5);
    double d3 = 1.0 + d2;

    REQUIRE(leq<double, epsilon>(d1, d2) == true);
    REQUIRE(leq<double, epsilon>(d2, d3) == true);

    float f1 = 0.2f;
    float f2 = 1 / std::sqrt(5.0f) / std::sqrt(5.0f);
    float f3 = 1.0f + f2;

    REQUIRE(leq<float, epsilon>(f1, f2) == true);
    REQUIRE(leq<float, epsilon>(f2, f3) == true);
}
