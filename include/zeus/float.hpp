#pragma once

#include "concepts.hpp"

#include <algorithm>
#include <concepts>
#include <limits>

namespace zeus
{
    // Note: To be removed in C++23. Superseded by std::abs
    template<ArithmeticType T>
    constexpr T abs(T x)
    {
        return x < T{0} ? -x : x;
    }

    template<std::floating_point T>
    constexpr bool almost_equal(T a, T b, T eps)
    {
        if (abs(a - b) <= eps)
        {
            return true;
        }

        return abs(a - b) <= eps * std::max(abs(a), abs(b));
    }

    template<std::floating_point T>
    constexpr bool almost_equal(T a, T b)
    {
        return almost_equal<T>(a, b, std::numeric_limits<T>::epsilon());
    }

    template<std::floating_point T>
    constexpr bool almost_zero(T a, T eps)
    {
        return abs(a) <= eps;
    }

    template<std::floating_point T>
    constexpr bool almost_zero(T a)
    {
        return almost_zero(a, std::numeric_limits<T>::epsilon());
    }
} // namespace zeus
