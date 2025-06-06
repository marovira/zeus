#pragma once

#include "concepts.hpp"

#include <concepts>
#include <type_traits>

namespace zeus
{
    template<UnsignedScopedEnum T>
    class EnumBitfield
    {
    public:
        using BaseType = std::underlying_type_t<T>;

        constexpr EnumBitfield() = default;

        constexpr explicit EnumBitfield(T val) :
            m_field{static_cast<BaseType>(val)}
        {}

        constexpr explicit EnumBitfield(BaseType field) :
            m_field{field}
        {}

        constexpr EnumBitfield& operator=(T val)
        {
            m_field = static_cast<BaseType>(val);
            return *this;
        }

        constexpr EnumBitfield& operator=(BaseType field)
        {
            m_field = field;
            return *this;
        }

        constexpr BaseType bits() const
        {
            return m_field;
        }

        constexpr T value() const
        {
            return static_cast<T>(m_field);
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

        constexpr EnumBitfield& operator^=(EnumBitfield const& rhs)
        {
            m_field ^= rhs.m_field;
            return *this;
        }

        constexpr EnumBitfield& operator^=(T rhs)
        {
            m_field ^= static_cast<BaseType>(rhs);
            return *this;
        }

        constexpr EnumBitfield operator&(EnumBitfield const& rhs) const
        {
            EnumBitfield tmp{*this};
            tmp &= rhs;
            return tmp;
        }

        constexpr EnumBitfield operator&(T rhs) const
        {
            EnumBitfield tmp{*this};
            tmp &= rhs;
            return tmp;
        }

        constexpr EnumBitfield operator|(EnumBitfield const& rhs) const
        {
            EnumBitfield tmp{*this};
            tmp |= rhs;
            return tmp;
        }

        constexpr EnumBitfield operator|(T rhs) const
        {
            EnumBitfield tmp{*this};
            tmp |= rhs;
            return tmp;
        }

        constexpr EnumBitfield operator^(EnumBitfield const& rhs) const
        {
            EnumBitfield tmp{*this};
            tmp ^= rhs;
            return tmp;
        }

        constexpr EnumBitfield operator^(T rhs) const
        {
            EnumBitfield tmp{*this};
            tmp ^= rhs;
            return tmp;
        }

        constexpr EnumBitfield operator~() const
        {
            EnumBitfield tmp{*this};
            tmp.m_field = ~m_field;
            return tmp;
        }

        template<typename U>
        requires std::integral<U>
        constexpr EnumBitfield operator>>(U n) const
        {
            EnumBitfield tmp{*this};
            tmp.m_field = m_field >> n;
            return tmp;
        }

        template<typename U>
        requires std::integral<U>
        constexpr EnumBitfield operator<<(U n) const
        {
            EnumBitfield tmp{*this};
            tmp.m_field = m_field << n;
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

    namespace enum_bitwise_operators
    {
        template<UnsignedScopedEnum T>
        constexpr EnumBitfield<T> operator&(T lhs, T rhs)
        {
            return EnumBitfield<T>{lhs} & EnumBitfield<T>{rhs};
        }

        template<UnsignedScopedEnum T>
        constexpr EnumBitfield<T> operator|(T lhs, T rhs)
        {
            return EnumBitfield<T>{lhs} | EnumBitfield<T>{rhs};
        }

        template<UnsignedScopedEnum T>
        constexpr EnumBitfield<T> operator^(T lhs, T rhs)
        {
            return EnumBitfield<T>{lhs} ^ EnumBitfield<T>{rhs};
        }

        template<UnsignedScopedEnum T>
        constexpr EnumBitfield<T> operator~(T val)
        {
            return ~EnumBitfield<T>{val};
        }

        template<UnsignedScopedEnum T, IntegralType U>
        constexpr EnumBitfield<T> operator>>(T val, U n)
        {
            return EnumBitfield<T>{val} >> n;
        }

        template<UnsignedScopedEnum T, IntegralType U>
        constexpr EnumBitfield<T> operator<<(T val, U n)
        {
            return EnumBitfield<T>{val} << n;
        }
    } // namespace enum_bitwise_operators
} // namespace zeus
