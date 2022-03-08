#pragma once

#include "concepts.hpp"

namespace zeus
{
    template<typename T>
    requires is_scoped_enum<T> && is_unsigned_enum<T>
    inline constexpr bool check_flag(T bit_field, T flag)
    {
        using namespace magic_enum::bitwise_operators;

        T c      = bit_field & flag;
        auto res = magic_enum::enum_integer(c);
        return res != 0;
    }
} // namespace zeus
