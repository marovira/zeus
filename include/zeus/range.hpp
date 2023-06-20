#pragma once

#include "concepts.hpp"
#include "float.hpp"

#include <cmath>
#include <stdexcept>

namespace zeus
{
    template<typename T>
    requires is_arithmetic<T>
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
            m_start{begin},
            m_end{end},
            m_step{step}
        {
            if (step == T{0})
            {
                throw std::runtime_error{"error: step must be non-zero"};
            }
        }

        constexpr std::size_t size() const
        {
            T hi, lo, step;
            if (m_step > T{0})
            {
                lo   = m_start;
                hi   = m_end;
                step = m_step;
            }
            else
            {
                hi   = m_start;
                lo   = m_end;
                step = -m_step;
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
            using value_type = T;

            constexpr Iterator() :
                m_val{0},
                m_step{0}
            {}

            constexpr Iterator(T val, T step) :
                m_val{val},
                m_step{step}
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
                m_val += m_step;
                return *this;
            }

            constexpr Iterator operator++(int)
            {
                Iterator r{*this};
                ++r;
                return;
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
            T m_val, m_step;
        };

        constexpr Iterator begin() const
        {
            return Iterator{m_start, m_step};
        }

        constexpr Iterator end() const
        {
            return Iterator{m_end, m_step};
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

    private:
        T m_start{0}, m_end{0}, m_step{0};
    };

    template<typename T>
    requires is_arithmetic<T>
    constexpr Range<T> range(T end)
    {
        return Range<T>{end};
    }

    template<typename T>
    requires is_arithmetic<T>
    constexpr Range<T> range(T begin, T end)
    {
        return Range<T>{begin, end};
    }

    template<typename T>
    requires is_arithmetic<T>
    constexpr Range<T> range(T begin, T end, T step)
    {
        return Range<T>{begin, end, step};
    }

} // namespace zeus
