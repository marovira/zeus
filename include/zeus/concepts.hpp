#pragma once

#include <magic_enum.hpp>
#include <string>
#include <string_view>
#include <type_traits>

namespace zeus
{
    template<typename T>
    concept is_enum = std::is_enum_v<T>;

    // Note: To be removed in C++23. Superseded by std::is_scoped_enum.
    template<typename T>
    concept is_scoped_enum = magic_enum::is_scoped_enum<T>::value;

    template<typename T>
    concept is_unsigned_enum = std::is_unsigned_v<std::underlying_type_t<T>>;

    template<typename T>
    concept is_unsigned_scoped_enum = is_scoped_enum<T> && is_unsigned_enum<T>;

    template<typename T>
    concept is_arithmetic = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template<typename T>
    concept is_string =
        std::is_convertible_v<T, std::string> || std::is_convertible_v<T, std::wstring>;

    template<typename T>
    concept is_string_view = std::is_convertible_v<T, std::string_view>
                             || std::is_convertible_v<T, std::wstring_view>;
} // namespace zeus
