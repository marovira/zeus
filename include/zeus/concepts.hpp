#pragma once

#include <magic_enum/magic_enum.hpp>
#include <type_traits>

namespace zeus
{
    template<typename T>
    concept Enum = std::is_enum_v<T>;

    // Note: to be removed in C++23. Superseded by std::is_scoped_enum
    template<typename T>
    concept ScopedEnum = magic_enum::is_scoped_enum<T>::value;

    template<typename T>
    concept UnsignedEnum = Enum<T> && std::is_unsigned_v<std::underlying_type_t<T>>;

    template<typename T>
    concept UnsignedScopedEnum = ScopedEnum<T> && UnsignedEnum<T>;

    template<typename T>
    concept Integral = std::is_integral_v<T> && !std::is_same_v<bool, T>;

    template<typename T>
    concept Arithmetic = Integral<T> || std::is_floating_point_v<T>;
} // namespace zeus
