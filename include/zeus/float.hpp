#pragma once

#include <cmath>
#include <concepts>
#include <cstdlib>
#include <functional>
#include <limits>

namespace zeus
{
    template<typename T>
    requires std::floating_point<T>
    using EpsilonFun = T (*)();

    template<typename T>
    requires std::floating_point<T>
    inline constexpr bool are_equal(T a, T b)
    {
        const T scale = (std::abs(a) + std::abs(b)) / static_cast<T>(2.0);
        return std::abs(a - b) <= std::numeric_limits<T>::epsilon() * scale;
    }

    template<typename T, EpsilonFun<T> epsilon>
    requires std::floating_point<T>
    inline constexpr bool are_equal(T a, T b)
    {
        const T scale = (std::abs(a) + std::abs(b)) / static_cast<T>(2.0);
        return std::abs(a - b) <= epsilon() * scale;
    }

    template<typename T>
    requires std::floating_point<T>
    inline constexpr bool is_zero(T a)
    {
        return are_equal<T>(a, static_cast<T>(0));
    }

    template<typename T, EpsilonFun<T> epsilon>
    requires std::floating_point<T>
    inline constexpr bool is_zero(T a)
    {
        return are_equal<T, epsilon>(a, static_cast<T>(0));
    }

    template<typename T>
    requires std::floating_point<T>
    inline constexpr bool geq(T a, T b)
    {
        return (a > b) || are_equal<T>(a, b);
    }

    template<typename T, EpsilonFun<T> epsilon>
    requires std::floating_point<T>
    inline constexpr bool geq(T a, T b)
    {
        return (a > b) || are_equal<T, epsilon>(a, b);
    }

    template<typename T>
    requires std::floating_point<T>
    inline constexpr bool leq(T a, T b)
    {
        return (a < b) || are_equal<T>(a, b);
    }

    template<typename T, EpsilonFun<T> epsilon>
    requires std::floating_point<T>
    inline constexpr bool leq(T a, T b)
    {
        return (a < b) || are_equal<T, epsilon>(a, b);
    }
} // namespace zeus
