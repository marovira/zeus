#pragma once

#include "assert.hpp"

#include <array>
#include <functional>
#include <numeric>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>

namespace zeus
{
    template<unsigned int N>
    struct factorial
    {
        static constexpr auto value{N * factorial<N - 1>::value};
    };

    template<>
    struct factorial<0>
    {
        static constexpr auto value{1u};
    };

    template<unsigned int N, unsigned int K>
    struct choose
    {
        static_assert(K <= N);
        static constexpr auto value{
            factorial<N>::value /
            (factorial<K>::value * factorial<N - K>::value)};
    };

    template<typename T, std::size_t N, std::size_t M = choose<N, 2>::value>
    constexpr std::array<std::pair<T, T>, M>
    choose_pairs(std::array<T, N> const& list)
    {
        using Pair = std::pair<T, T>;

        static_assert(N > 1);

        if constexpr (N == 2)
        {
            return {{{list[0], list[1]}}};
        }
        else
        {
            std::array<Pair, M> result;
            std::size_t k{0};
            for (std::size_t i{0}; i < N; ++i)
            {
                for (std::size_t j{i + 1}; j < N; ++j)
                {
                    result[k] = {list[i], list[j]};
                    ++k;
                }
            }

            return result;
        }
    }
} // namespace zeus
