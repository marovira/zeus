#pragma once

#include "assert.hpp"

#include <functional>
#include <numeric>
#include <unordered_set>
#include <utility>
#include <vector>

namespace zeus
{
    template<typename T>
    constexpr std::vector<std::pair<T, T>>
    find_unique_pairs(std::vector<T> const& list)
    {
        ASSERT(list.size() >= 2);

        if (list.size() == 2)
        {
            return {{list[0], list[1]}};
        }

        using Pair = std::pair<T, T>;

        auto pair_hash = [](Pair const& p) {
            return std::hash<T>()(p.first) + std::hash<T>()(p.second);
        };

        auto pair_equal = [](Pair const& left, Pair const& right) {
            return (left.first == right.first && left.second == right.second) ||
                   (left.first == right.second && left.second == right.first);
        };

        std::unordered_set<Pair, decltype(pair_hash), decltype(pair_equal)>
            unique_pairs(0, pair_hash, pair_equal);

        for (auto& val1 : list)
        {
            for (auto& val2 : list)
            {
                if (val1 == val2)
                {
                    continue;
                }

                unique_pairs.insert({val1, val2});
            }
        }

        std::vector<Pair> result(unique_pairs.size());
        result.assign(unique_pairs.begin(), unique_pairs.end());
        return result;
    }
} // namespace zeus
