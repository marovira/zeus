#pragma once

#include <cmath>
#include <cstdlib>
#include <functional>
#include <limits>
#include <type_traits>

namespace zeus
{
    template<typename T,
             typename = std::enable_if<std::is_floating_point<T>::value>>
    using epsilon_fn = T (*)();

    template<typename T,
             typename = std::enable_if<std::is_floating_point<T>::value>>
    inline constexpr bool are_equal(T a, T b)
    {
        const T scale = (std::abs(a) + std::abs(b)) / static_cast<T>(2.0);
        return std::abs(a - b) <= std::numeric_limits<T>::epsilon() * scale;
    }

    template<typename T,
             epsilon_fn<T> epsilon,
             typename = std::enable_if<std::is_floating_point<T>::value>>
    inline constexpr bool are_equal(T a, T b)
    {
        const T scale = (std::abs(a) + std::abs(b)) / static_cast<T>(2.0);
        return std::abs(a - b) <= epsilon() * scale;
    }

    template<typename T,
             typename = std::enable_if<std::is_floating_point<T>::value>>
    inline constexpr bool is_zero(T a)
    {
        return are_equal<T>(a, static_cast<T>(0));
    }

    template<typename T,
             epsilon_fn<T> epsilon,
             typename = std::enable_if<std::is_floating_point<T>::value>>
    inline constexpr bool is_zero(T a)
    {
        return are_equal<T, epsilon>(a, static_cast<T>(0));
    }

    template<typename T,
             typename = std::enable_if<std::is_floating_point<T>::value>>
    inline constexpr bool geq(T a, T b)
    {
        return (a > b) || are_equal<T>(a, b);
    }

    template<typename T,
             epsilon_fn<T> epsilon,
             typename = std::enable_if<std::is_floating_point<T>::value>>
    inline constexpr bool geq(T a, T b)
    {
        return (a > b) || are_equal<T, epsilon>(a, b);
    }

    template<typename T,
             typename = std::enable_if<std::is_floating_point<T>::value>>
    inline constexpr bool leq(T a, T b)
    {
        return (a < b) || are_equal<T>(a, b);
    }

    template<typename T,
             epsilon_fn<T> epsilon,
             typename = std::enable_if<std::is_floating_point<T>::value>>
    inline constexpr bool leq(T a, T b)
    {
        return (a < b) || are_equal<T, epsilon>(a, b);
    }
} // namespace zeus
