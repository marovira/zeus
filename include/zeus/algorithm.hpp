#pragma once

#include <array>
#include <cstddef>
#include <utility>

namespace zeus
{
    template<unsigned int N>
    struct Factorial
    {
        static constexpr auto value{N * Factorial<N - 1>::value};
    };

    template<>
    struct Factorial<0>
    {
        static constexpr auto value{1u};
    };

    template<unsigned int N, unsigned int K>
    struct Choose
    {
        static_assert(K <= N);
        static constexpr auto value{Factorial<N>::value
                                    / (Factorial<K>::value * Factorial<N - K>::value)};
    };

    template<typename T, std::size_t N, std::size_t M = Choose<N, 2>::value>
    constexpr auto choose_pairs(std::array<T, N> const& list)
        -> std::array<std::pair<T, T>, M>
    {
        using Pair = std::pair<T, T>;

        static_assert(N > 1);

        if constexpr (N == 2)
        {
            return {{{list[0], list[1]}}};
        }
        else
        {
            auto result = std::array<Pair, M>{};
            auto k = std::size_t{0};
            for (auto i = std::size_t{0}; i < N; ++i)
            {
                for (auto j{i + 1}; j < N; ++j)
                {
                    result[k] = {list[i], list[j]};
                    ++k;
                }
            }

            return result;
        }
    }
} // namespace zeus
