#pragma once

#include "concepts.hpp"

#include <chrono>

namespace zeus
{
    template<ArithmeticType T, typename Res = std::chrono::high_resolution_clock>
    class Timer
    {
    public:
        void start()
        {
            m_begin = Res::now();
            m_split = m_begin;
        }

        void reset()
        {
            m_begin = {};
            m_split = {};
        }

        T elapsed() const
        {
            return time_diff(m_begin);
        }

        T split() const
        {
            if (m_split == TimePoint{})
            {
                return 0;
            }

            T diff  = time_diff(m_split);
            m_split = Res::now();
            return diff;
        }

    private:
        using Duration  = std::chrono::duration<T>;
        using TimePoint = std::chrono::time_point<Res>;

        T time_diff(TimePoint const& first) const
        {
            return std::chrono::duration_cast<Duration>(Res::now() - first).count();
        }

        TimePoint m_begin;
        mutable TimePoint m_split;
    };
} // namespace zeus
