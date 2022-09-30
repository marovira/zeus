#pragma once

#include "concepts.hpp"

namespace zeus
{
    template<typename T>
    requires is_scoped_enum<T> && is_unsigned_enum<T>
    class EnumBitfield
    {
    public:
        using BaseType = std::underlying_type_t<T>;

        constexpr EnumBitfield() = default;
        constexpr explicit EnumBitfield(T val) :
            m_field{static_cast<BaseType>(val)}
        {}

        constexpr BaseType get() const
        {
            return m_field;
        }

        constexpr EnumBitfield& operator&=(EnumBitfield const& rhs)
        {
            m_field &= rhs.m_field;
            return *this;
        }

        constexpr EnumBitfield& operator&=(T rhs)
        {
            m_field &= static_cast<BaseType>(rhs);
            return *this;
        }

        constexpr EnumBitfield& operator|=(EnumBitfield const& rhs)
        {
            m_field |= rhs.m_field;
            return *this;
        }

        constexpr EnumBitfield& operator|=(T rhs)
        {
            m_field |= static_cast<BaseType>(rhs);
            return *this;
        }

        constexpr EnumBitfield operator&(EnumBitfield const& rhs)
        {
            EnumBitfield tmp{*this};
            tmp &= rhs;
            return tmp;
        }

        constexpr EnumBitfield operator&(T rhs)
        {
            EnumBitfield tmp{*this};
            tmp &= rhs;
            return tmp;
        }

        constexpr EnumBitfield operator|(EnumBitfield const& rhs)
        {
            EnumBitfield tmp{*this};
            tmp |= rhs;
            return tmp;
        }

        constexpr EnumBitfield operator|(T rhs)
        {
            EnumBitfield tmp{*this};
            tmp |= rhs;
            return tmp;
        }

        constexpr operator bool() const
        {
            return static_cast<bool>(m_field);
        }

        constexpr bool operator==(EnumBitfield const& rhs) const
        {
            return m_field == rhs.m_field;
        }

        constexpr bool operator==(T rhs) const
        {
            return m_field == static_cast<BaseType>(rhs);
        }

        constexpr bool operator!=(EnumBitfield const& rhs) const
        {
            return !(*this == rhs);
        }

        constexpr bool operator!=(T rhs) const
        {
            return !(*this == rhs);
        }

    private:
        BaseType m_field{0};
    };

    template<typename T>
    requires is_scoped_enum<T> && is_unsigned_enum<T>
    [[deprecated]] inline constexpr bool check_flag(T bit_field, T flag)
    {
        using namespace magic_enum::bitwise_operators;

        T c      = bit_field & flag;
        auto res = magic_enum::enum_integer(c);
        return res != 0;
    }
} // namespace zeus
