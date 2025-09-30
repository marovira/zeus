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

        auto elapsed() const -> T
        {
            return time_diff(m_begin);
        }

        auto split() const -> T
        {
            if (m_split == TimePoint{})
            {
                return 0;
            }

            auto diff = time_diff(m_split);
            m_split = Res::now();
            return diff;
        }

    private:
        using Duration = std::chrono::duration<T>;
        using TimePoint = std::chrono::time_point<Res>;

        auto time_diff(TimePoint const& first) const -> T
        {
            return std::chrono::duration_cast<Duration>(Res::now() - first).count();
        }

        TimePoint m_begin;
        mutable TimePoint m_split;
    };
} // namespace zeus
