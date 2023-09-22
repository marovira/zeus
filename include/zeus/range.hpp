#pragma once

#include "concepts.hpp"
#include "float.hpp"

#include <cmath>
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

        constexpr std::size_t size() const
        {
            T hi, lo, step;
            if (m_stride > T{0})
            {
                lo   = m_begin;
                hi   = m_end;
                step = m_stride;
            }
            else
            {
                hi   = m_begin;
                lo   = m_end;
                step = -m_stride;
            }

            if (lo >= hi)
            {
                return 0;
            }

            return static_cast<std::size_t>((hi - lo - 1) / step + 1);
        }

        constexpr bool empty() const
        {
            return size() == 0;
        }

        class Iterator
        {
        public:
            using value_type        = T;
            using difference_type   = std::ptrdiff_t;
            using reference         = T&;
            using pointer           = T*;
            using iterator_category = std::forward_iterator_tag;

            constexpr Iterator() :
                m_val{0},
                m_stride{0}
            {}

            constexpr Iterator(T val, T step) :
                m_val{val},
                m_stride{step}
            {}

            constexpr const T operator*() const
            {
                return m_val;
            }

            constexpr const T* operator->() const
            {
                return &m_val;
            }

            constexpr Iterator& operator++()
            {
                m_val += m_stride;
                return *this;
            }

            constexpr Iterator operator++(int)
            {
                Iterator r{*this};
                ++r;
                return r;
            }

            constexpr bool operator==(Iterator const& rhs) const
            {
                return m_val == rhs.m_val;
            }

            constexpr bool operator!=(Iterator const& rhs) const
            {
                return !(*this == rhs);
            }

        private:
            T m_val, m_stride;
        };

        constexpr Iterator begin() const
        {
            return Iterator{m_begin, m_stride};
        }

        constexpr Iterator end() const
        {
            return Iterator{m_begin + ((static_cast<T>(size())) * m_stride), m_stride};
        }

        constexpr bool operator==(Range const& rhs) const
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

        constexpr bool operator!=(Range const& rhs) const
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
    constexpr Range<T> range(T end)
    {
        return Range<T>{end};
    }

    template<ArithmeticType T>
    constexpr Range<T> range(T begin, T end)
    {
        return Range<T>{begin, end};
    }

    template<ArithmeticType T>
    constexpr Range<T> range(T begin, T end, T step)
    {
        return Range<T>{begin, end, step};
    }

} // namespace zeus
