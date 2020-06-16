#include <zeus/algorithm.hpp>

#include <catch2/catch.hpp>

TEST_CASE("[algorithm] - find_unique_pairs: list of size 2", "[zeus]")
{
    std::vector<int> list{1, 2};

    auto result = zeus::find_unique_pairs(list);

    std::vector<std::pair<int, int>> expected{{1, 2}};

    REQUIRE(result.size() == expected.size());
    REQUIRE(result == expected);
}

TEST_CASE("[algorithm] - find_unique_pairs: list of size 3", "[zeus]")
{
    std::vector<int> list{1, 2, 3};

    auto result = zeus::find_unique_pairs(list);

    std::vector<std::pair<int, int>> expected{{1, 2}, {1, 3}, {2, 3}};

    REQUIRE(result.size() == expected.size());
    REQUIRE(result == expected);
}

TEST_CASE("[algorithm] - find_unique_pairs: list of size n", "[zeus]")
{
    std::vector<int> list{1, 2, 3, 4, 5, 6};

    auto result = zeus::find_unique_pairs(list);
    std::sort(result.begin(), result.end());

    std::vector<std::pair<int, int>> expected{{1, 2},
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
                                              {5, 6}};

    REQUIRE(result.size() == expected.size());
    REQUIRE(result == expected);
}
