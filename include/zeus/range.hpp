#pragma once

#include "concepts.hpp"

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <vector>

namespace zeus
{
    template<ArithmeticType T>
    class Range
    {
    public:
        constexpr Range(T end) :
            Range{0, end, 1}
        {}

        constexpr Range(T begin, T end) :
            Range{begin, end, 1}
        {}

        constexpr Range(T begin, T end, T step) :
            m_begin{begin},
            m_end{end},
            m_stride{step}
        {
            if (step == T{0})
            {
                throw std::runtime_error{"error: step must be non-zero"};
            }
        }

        [[nodiscard]]
        constexpr auto size() const -> std::size_t
        {
            auto hi = T{};
            auto lo = T{};
            auto step = T{};
            if (m_stride > T{0})
            {
                lo = m_begin;
                hi = m_end;
                step = m_stride;
            }
            else
            {
                hi = m_begin;
                lo = m_end;
                step = -m_stride;
            }

            if (lo >= hi)
            {
                return 0;
            }

            return static_cast<std::size_t>((hi - lo - 1) / step + 1);
        }

        [[nodiscard]]
        constexpr auto empty() const -> bool
        {
            return size() == 0;
        }

        class Iterator
        {
        public:
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using reference = T&;
            using pointer = T*;
            using iterator_category = std::forward_iterator_tag;

            constexpr Iterator() :
                m_val{0},
                m_stride{0}
            {}

            constexpr Iterator(T val, T step) :
                m_val{val},
                m_stride{step}
            {}

            constexpr auto operator*() const -> const T
            {
                return m_val;
            }

            constexpr auto operator->() const -> const T*
            {
                return &m_val;
            }

            constexpr auto operator++() -> Iterator&
            {
                m_val += m_stride;
                return *this;
            }

            constexpr auto operator++(int) -> Iterator
            {
                Iterator r{*this};
                ++r;
                return r;
            }

            constexpr auto operator==(Iterator const& rhs) const -> bool
            {
                return m_val == rhs.m_val;
            }

            constexpr auto operator!=(Iterator const& rhs) const -> bool
            {
                return !(*this == rhs);
            }

        private:
            T m_val, m_stride;
        };

        constexpr auto begin() const -> Iterator
        {
            return Iterator{m_begin, m_stride};
        }

        constexpr auto end() const -> Iterator
        {
            return Iterator{m_begin + ((static_cast<T>(size())) * m_stride), m_stride};
        }

        constexpr auto operator==(Range const& rhs) const -> bool
        {
            if (size() != rhs.size())
            {
                return false;
            }

            for (auto it{begin()}, other{rhs.begin()}; it != end() && other != rhs.end();
                 ++it, ++other)
            {
                if (*it != *other)
                {
                    return false;
                }
            }

            return true;
        }

        constexpr auto operator!=(Range const& rhs) const -> bool
        {
            return !(*this == rhs);
        }

        constexpr explicit operator std::vector<T>() const
        {
            return std::vector<T>{begin(), end()};
        }

    private:
        T m_begin{0}, m_end{0}, m_stride{0};
    };

    template<ArithmeticType T>
    constexpr auto range(T end) -> Range<T>
    {
        return Range<T>{end};
    }

    template<ArithmeticType T>
    constexpr auto range(T begin, T end) -> Range<T>
    {
        return Range<T>{begin, end};
    }

    template<ArithmeticType T>
    constexpr auto range(T begin, T end, T step) -> Range<T>
    {
        return Range<T>{begin, end, step};
    }
} // namespace zeus
