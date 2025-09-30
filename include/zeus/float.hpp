#pragma once

#include "concepts.hpp"

#include <algorithm>
#include <concepts>
#include <limits>

namespace zeus
{
    // Note: To be removed in C++23. Superseded by std::abs
    template<ArithmeticType T>
    constexpr auto abs(T x) -> T
    {
        return x < T{0} ? -x : x;
    }

    template<std::floating_point T>
    constexpr auto almost_equal(T a, T b, T eps) -> bool
    {
        if (abs(a - b) <= eps)
        {
            return true;
        }

        return abs(a - b) <= eps * std::max(abs(a), abs(b));
    }

    template<std::floating_point T>
    constexpr auto almost_equal(T a, T b) -> bool
    {
        return almost_equal<T>(a, b, std::numeric_limits<T>::epsilon());
    }

    template<std::floating_point T>
    constexpr auto almost_zero(T a, T eps) -> bool
    {
        return abs(a) <= eps;
    }

    template<std::floating_point T>
    constexpr auto almost_zero(T a) -> bool
    {
        return almost_zero(a, std::numeric_limits<T>::epsilon());
    }
} // namespace zeus
