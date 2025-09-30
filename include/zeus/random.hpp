#pragma once

#include "concepts.hpp"

#include <limits>
#include <random>

namespace zeus
{
    template<ArithmeticType T, typename Engine = std::mt19937>
    class Random
    {
    public:
        Random() = default;

        Random(typename Engine::result_type seed) :
            m_engine{seed}
        {}

        auto get_random_in_range(T min, T max) -> T
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                auto dist = std::uniform_real_distribution<T>{min, max};
                return dist(m_engine);
            }
            else
            {
                auto dist = std::uniform_int_distribution<T>{min, max};
                return dist(m_engine);
            }
        }

        auto get_random_zero_to_max() -> T
        {
            return get_random_in_range(static_cast<T>(0), std::numeric_limits<T>::max());
        }

        auto get_random_zero_to_one() -> T
        {
            return get_random_in_range(static_cast<T>(0), static_cast<T>(1));
        }

    private:
        Engine m_engine{std::random_device{}()};
    };
} // namespace zeus
