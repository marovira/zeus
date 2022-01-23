#pragma once

#include <chrono>

namespace zeus
{
    template<typename T, typename Res = std::chrono::high_resolution_clock>
    class Timer
    {
    public:
        constexpr void start()
        {
            m_begin = Res::now();
            m_split = m_begin;
        }

        constexpr void reset()
        {
            m_begin = {};
            m_split = {};
        }

        constexpr T elapsed() const
        {
            return time_diff(m_begin);
        }

        constexpr T split() const
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

        constexpr T time_diff(TimePoint const& first) const
        {
            return std::chrono::duration_cast<Duration>(Res::now() - first)
                .count();
        }

        TimePoint m_begin;
        mutable TimePoint m_split;
    };
} // namespace zeus
