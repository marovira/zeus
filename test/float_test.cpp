#include <zeus/float.hpp>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

TEMPLATE_TEST_CASE("[float] - abs", "[zeus]", float, double)
{
    SECTION("Runtime")
    {
        REQUIRE(zeus::abs(TestType{0}) == TestType{0});
        REQUIRE(zeus::abs(TestType{1}) == TestType{1});
        REQUIRE(zeus::abs(TestType{-1}) == TestType{1});
    }

    SECTION("Compile-time")
    {
        constexpr auto val1 = []() {
            return zeus::abs(TestType{0});
        }();

        constexpr auto val2 = []() {
            return zeus::abs(TestType{1});
        }();

        constexpr auto val3 = []() {
            return zeus::abs(TestType{-1});
        }();

        STATIC_REQUIRE(val1 == TestType{0});
        STATIC_REQUIRE(val2 == TestType{1});
        STATIC_REQUIRE(val3 == TestType{1});
    }
}

TEMPLATE_TEST_CASE("[float] - almost_equal", "[zeus]", float, double)
{
    using zeus::almost_equal;
    using T = TestType;

    SECTION("Runtime")
    {
        REQUIRE(almost_equal(T{3.145646}, T{3.145646}));
        REQUIRE(almost_equal(T{145697.78965}, T{145553.09186}, T{0.001}));
        REQUIRE(almost_equal(T{1.0}, T{1.0}, T{0.0}));
        REQUIRE(almost_equal(T{0.123456}, T{0.123457}, T{1E-3}));
        REQUIRE(almost_equal(T{1.23456E28}, T{1.23457E28}, T{1E-3}));
        REQUIRE(almost_equal(T{1.23456E-10}, T{1.23457E-10}, T{1E-3}));
        REQUIRE(almost_equal(T{1.111E-10}, T{1.112E-10}, T{0.1}));
        REQUIRE(almost_equal(T{1.0}, T{1.0001}, T{1.1E-2}));
        REQUIRE(almost_equal(T{1.0002}, T{1.0001}, T{1.1E-2}));

        REQUIRE_FALSE(almost_equal(T{145697.78965}, T{145552.09186}, T{0.001}));
        REQUIRE_FALSE(almost_equal(T{0.123456}, T{-0.123457}, T{1E-3}));
        REQUIRE_FALSE(almost_equal(T{1.0}, T{1.0002}, T{1.1E-4}));
    }

    SECTION("Compile-time")
    {
        STATIC_REQUIRE(almost_equal(T{3.145646}, T{3.145646}));
        STATIC_REQUIRE(almost_equal(T{145697.78965}, T{145553.09186}, T{0.001}));
        STATIC_REQUIRE(almost_equal(T{1.0}, T{1.0}, T{0.0}));
        STATIC_REQUIRE(almost_equal(T{0.123456}, T{0.123457}, T{1E-3}));
        STATIC_REQUIRE(almost_equal(T{1.23456E28}, T{1.23457E28}, T{1E-3}));
        STATIC_REQUIRE(almost_equal(T{1.23456E-10}, T{1.23457E-10}, T{1E-3}));
        STATIC_REQUIRE(almost_equal(T{1.111E-10}, T{1.112E-10}, T{0.1}));
        STATIC_REQUIRE(almost_equal(T{1.0}, T{1.0001}, T{1.1E-2}));
        STATIC_REQUIRE(almost_equal(T{1.0002}, T{1.0001}, T{1.1E-2}));

        STATIC_REQUIRE_FALSE(almost_equal(T{145697.78965}, T{145552.09186}, T{0.001}));
        STATIC_REQUIRE_FALSE(almost_equal(T{0.123456}, T{-0.123457}, T{1E-3}));
        STATIC_REQUIRE_FALSE(almost_equal(T{1.0}, T{1.0002}, T{1.1E-4}));
    }
}

TEMPLATE_TEST_CASE("[float] - is_zero", "[zeus]", float, double)
{
    using zeus::almost_zero;
    using T = TestType;

    SECTION("Runtime")
    {
        REQUIRE(almost_zero(T{0.0}));
        REQUIRE(almost_zero(T{1E-20}));
        REQUIRE(almost_zero(T{1E-30}));
        REQUIRE(almost_zero(T{-1E-10}, T{1E-9}));

        REQUIRE_FALSE(almost_zero(T{-1E-10}, T{1E-11}));
    }

    SECTION("Compile-time")
    {
        STATIC_REQUIRE(almost_zero(T{0.0}));
        STATIC_REQUIRE(almost_zero(T{1E-20}));
        STATIC_REQUIRE(almost_zero(T{1E-30}));
        STATIC_REQUIRE(almost_zero(T{-1E-10}, T{1E-9}));

        STATIC_REQUIRE_FALSE(almost_zero(T{-1E-10}, T{1E-11}));
    }
}
