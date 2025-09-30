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

        constexpr auto operator=(T val) -> EnumBitfield&
        {
            m_field = static_cast<BaseType>(val);
            return *this;
        }

        constexpr auto operator=(BaseType field) -> EnumBitfield&
        {
            m_field = field;
            return *this;
        }

        constexpr auto bits() const -> BaseType
        {
            return m_field;
        }

        constexpr auto value() const -> T
        {
            return static_cast<T>(m_field);
        }

        constexpr auto operator&=(EnumBitfield const& rhs) -> EnumBitfield&
        {
            m_field &= rhs.m_field;
            return *this;
        }

        constexpr auto operator&=(T rhs) -> EnumBitfield&
        {
            m_field &= static_cast<BaseType>(rhs);
            return *this;
        }

        constexpr auto operator|=(EnumBitfield const& rhs) -> EnumBitfield&
        {
            m_field |= rhs.m_field;
            return *this;
        }

        constexpr auto operator|=(T rhs) -> EnumBitfield&
        {
            m_field |= static_cast<BaseType>(rhs);
            return *this;
        }

        constexpr auto operator^=(EnumBitfield const& rhs) -> EnumBitfield&
        {
            m_field ^= rhs.m_field;
            return *this;
        }

        constexpr auto operator^=(T rhs) -> EnumBitfield&
        {
            m_field ^= static_cast<BaseType>(rhs);
            return *this;
        }

        constexpr auto operator&(EnumBitfield const& rhs) const -> EnumBitfield
        {
            EnumBitfield tmp{*this};
            tmp &= rhs;
            return tmp;
        }

        constexpr auto operator&(T rhs) const -> EnumBitfield
        {
            EnumBitfield tmp{*this};
            tmp &= rhs;
            return tmp;
        }

        constexpr auto operator|(EnumBitfield const& rhs) const -> EnumBitfield
        {
            EnumBitfield tmp{*this};
            tmp |= rhs;
            return tmp;
        }

        constexpr auto operator|(T rhs) const -> EnumBitfield
        {
            EnumBitfield tmp{*this};
            tmp |= rhs;
            return tmp;
        }

        constexpr auto operator^(EnumBitfield const& rhs) const -> EnumBitfield
        {
            EnumBitfield tmp{*this};
            tmp ^= rhs;
            return tmp;
        }

        constexpr auto operator^(T rhs) const -> EnumBitfield
        {
            EnumBitfield tmp{*this};
            tmp ^= rhs;
            return tmp;
        }

        constexpr auto operator~() const -> EnumBitfield
        {
            EnumBitfield tmp{*this};
            tmp.m_field = ~m_field;
            return tmp;
        }

        template<typename U>
        requires std::integral<U>
        constexpr auto operator>>(U n) const -> EnumBitfield
        {
            EnumBitfield tmp{*this};
            tmp.m_field = m_field >> n;
            return tmp;
        }

        template<typename U>
        requires std::integral<U>
        constexpr auto operator<<(U n) const -> EnumBitfield
        {
            EnumBitfield tmp{*this};
            tmp.m_field = m_field << n;
            return tmp;
        }

        constexpr operator bool() const
        {
            return static_cast<bool>(m_field);
        }

        constexpr auto operator==(EnumBitfield const& rhs) const -> bool
        {
            return m_field == rhs.m_field;
        }

        constexpr auto operator==(T rhs) const -> bool
        {
            return m_field == static_cast<BaseType>(rhs);
        }

        constexpr auto operator!=(EnumBitfield const& rhs) const -> bool
        {
            return !(*this == rhs);
        }

        constexpr auto operator!=(T rhs) const -> bool
        {
            return !(*this == rhs);
        }

    private:
        BaseType m_field{0};
    };

    namespace enum_bitwise_operators
    {
        template<UnsignedScopedEnum T>
        constexpr auto operator&(T lhs, T rhs) -> EnumBitfield<T>
        {
            return EnumBitfield<T>{lhs} & EnumBitfield<T>{rhs};
        }

        template<UnsignedScopedEnum T>
        constexpr auto operator|(T lhs, T rhs) -> EnumBitfield<T>
        {
            return EnumBitfield<T>{lhs} | EnumBitfield<T>{rhs};
        }

        template<UnsignedScopedEnum T>
        constexpr auto operator^(T lhs, T rhs) -> EnumBitfield<T>
        {
            return EnumBitfield<T>{lhs} ^ EnumBitfield<T>{rhs};
        }

        template<UnsignedScopedEnum T>
        constexpr auto operator~(T val) -> EnumBitfield<T>
        {
            return ~EnumBitfield<T>{val};
        }

        template<UnsignedScopedEnum T, IntegralType U>
        constexpr auto operator>>(T val, U n) -> EnumBitfield<T>
        {
            return EnumBitfield<T>{val} >> n;
        }

        template<UnsignedScopedEnum T, IntegralType U>
        constexpr auto operator<<(T val, U n) -> EnumBitfield<T>
        {
            return EnumBitfield<T>{val} << n;
        }
    } // namespace enum_bitwise_operators
} // namespace zeus
