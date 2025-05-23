#include <zeus/algorithm.hpp>

#include <catch2/catch_test_macros.hpp>

#include <array>
#include <utility>

TEST_CASE("[algorithm] - Factorial", "[zeus]")
{
    SECTION("Base case")
    {
        STATIC_REQUIRE(zeus::Factorial<0>::value == 1);
    }

    SECTION("General case")
    {
        STATIC_REQUIRE(zeus::Factorial<6>::value == 720);
    }
}

TEST_CASE("[algorithm] - Choose", "[zeus]")
{
    SECTION("N choose 0")
    {
        STATIC_REQUIRE(zeus::Choose<3, 0>::value == 1);
    }

    SECTION("N choose k")
    {
        STATIC_REQUIRE(zeus::Choose<6, 2>::value == 15);
    }
}

TEST_CASE("[algorithm] - choose_pairs", "[zeus]")
{
    SECTION("List of size 2")
    {
        SECTION("Runtime")
        {
            const std::array<int, 2> list{1, 2};
            auto result = zeus::choose_pairs(list);
            REQUIRE(result.size() == 1);
            REQUIRE(result[0] == std::pair<int, int>{1, 2});
        }

        SECTION("Compile-time")
        {
            const static constexpr auto result = []() {
                const std::array<int, 2> list{1, 2};
                return zeus::choose_pairs(list);
            }();

            STATIC_REQUIRE(result.size() == 1);
            STATIC_REQUIRE(result[0] == std::pair<int, int>{1, 2});
        }
    }

    SECTION("List of size 3")
    {
        constexpr std::array<std::pair<int, int>, 3> expected{
            {{1, 2}, {1, 3}, {2, 3}}
        };

        SECTION("Runtime")
        {
            const std::array<int, 3> list{1, 2, 3};
            auto result = zeus::choose_pairs(list);

            REQUIRE(result == expected);
        }

        SECTION("Compile-time")
        {
            static constexpr auto result = []() {
                const std::array<int, 3> list{1, 2, 3};
                return zeus::choose_pairs(list);
            }();

            STATIC_REQUIRE(result == expected);
        }
    }

    SECTION("List of size n")
    {
        constexpr std::array<std::pair<int, int>, 15> expected{
            {{1, 2},
             {1, 3},
             {1, 4},
             {1, 5},
             {1, 6},
             {2, 3},
             {2, 4},
             {2, 5},
             {2, 6},
             {3, 4},
             {3, 5},
             {3, 6},
             {4, 5},
             {4, 6},
             {5, 6}}
        };

        SECTION("Runtime")
        {
            const std::array<int, 6> list{1, 2, 3, 4, 5, 6};
            auto result = zeus::choose_pairs(list);

            REQUIRE(result == expected);
        }

        SECTION("Compile-time")
        {
            static constexpr auto result = []() {
                const std::array<int, 6> list{1, 2, 3, 4, 5, 6};
                return zeus::choose_pairs(list);
            }();

            STATIC_REQUIRE(result == expected);
        }
    }
}
