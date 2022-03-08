#pragma once

#include <magic_enum.hpp>
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
} // namespace zeus
