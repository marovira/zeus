#include <zeus/algorithm.hpp>

#include <catch2/catch.hpp>

TEST_CASE("[algorithm] - factorial: base case", "[zeus]")
{
    REQUIRE(zeus::factorial<0>::value == 1);
}

TEST_CASE("[algorithm] - factorial: general case", "[zeus]")
{
    REQUIRE(zeus::factorial<6>::value == 720);
}

TEST_CASE("[algorithm] - choose: n choose 0", "[zeus]")
{
    REQUIRE(zeus::choose<3, 0>::value == 1);
}

TEST_CASE("[algorithm] - choose: n choose k", "[zeus]")
{
    REQUIRE(zeus::choose<6, 2>::value == 15);
}

TEST_CASE("[algorithm] - choose_pairs: list of size 2", "[zeus]")
{
    constexpr std::array<int, 2> list{1, 2};
    auto result = zeus::choose_pairs(list);

    REQUIRE(result[0] == std::pair<int, int>{1, 2});
}

TEST_CASE("[algorithm] - choose_pairs: list of size 3", "[zeus]")
{
    constexpr std::array<int, 3> list{1, 2, 3};
    constexpr std::array<std::pair<int, int>, 3> expected{
        {{1, 2}, {1, 3}, {2, 3}}};
    auto result = zeus::choose_pairs(list);

    REQUIRE(result == expected);
}

TEST_CASE("[algorithm - choose_pairs: list of size n", "[zeus]")
{
    constexpr std::array<int, 6> list{1, 2, 3, 4, 5, 6};
    constexpr std::array<std::pair<int, int>, 15> expected{{{1, 2},
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
                                                            {5, 6}}};
    auto result = zeus::choose_pairs(list);

    REQUIRE(result == expected);
}
