#include <zeus/linspace.hpp>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <vector>

TEMPLATE_TEST_CASE("[linspace] - linspace: main function", "[zeus]", float, double)
{
    const TestType start{0};
    const TestType end{1};
    SECTION("Empty")
    {
        auto ret = zeus::linspace(start, end, 0u, false);
        REQUIRE(ret.empty());
    }

    SECTION("1 step")
    {
        auto ret = zeus::linspace(start, end, 1u, false);
        REQUIRE(ret.size() == 1);
        REQUIRE(ret.front() == start);
    }

    SECTION("Invalid range")
    {
        REQUIRE_THROWS(zeus::linspace(end, start, 2u, false));
    }

    SECTION("Include end-point")
    {
        SECTION("2 steps")
        {
            const std::vector<TestType> exp{start, end};
            auto ret = zeus::linspace(start, end, 2u, true);
            REQUIRE(ret == exp);
        }

        SECTION("More than 2 steps")
        {
            const std::vector<TestType> exp{start, TestType{0.5}, end};
            auto ret = zeus::linspace(start, end, 3u, true);
            REQUIRE(ret == exp);
        }
    }

    SECTION("Skip end-point")
    {
        SECTION("2 steps")
        {
            const std::vector<TestType> exp{start, TestType{0.5}};
            auto ret = zeus::linspace(start, end, 2u, false);
            REQUIRE(ret == exp);
        }

        SECTION("More than 2 steps")
        {
            const std::vector<TestType> exp{start,
                                            TestType{0.25},
                                            TestType{0.5},
                                            TestType{0.75}};
            auto ret = zeus::linspace(start, end, 4u, false);
            REQUIRE(ret == exp);
        }
    }
}

TEMPLATE_TEST_CASE("[linspace] - linspace: overload", "[zeus]", float, double)
{
    const TestType start{0};
    const TestType end{1};

    SECTION("Empty")
    {
        auto ret = zeus::linspace(start, end, 0u);
        REQUIRE(ret.empty());
    }

    SECTION("1 step")
    {
        auto ret = zeus::linspace(start, end, 1u);
        REQUIRE(ret.size() == 1);
        REQUIRE(ret.front() == start);
    }

    SECTION("Invalid range")
    {
        REQUIRE_THROWS(zeus::linspace(end, start, 2u));
    }

    SECTION("2 steps")
    {
        const std::vector<TestType> exp{start, end};
        auto ret  = zeus::linspace(start, end, 2u);
        auto base = zeus::linspace(start, end, 2u, true);
        REQUIRE(ret == exp);
        REQUIRE(ret == base);
    }

    SECTION("More than 2 steps")
    {
        const std::vector<TestType> exp{start, TestType{0.5}, end};
        auto ret  = zeus::linspace(start, end, 3u);
        auto base = zeus::linspace(start, end, 3u, true);
        REQUIRE(ret == exp);
        REQUIRE(ret == base);
    }
}
