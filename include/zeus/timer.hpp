#pragma once

#include <chrono>

namespace zeus
{
    template<typename T, typename Res = std::chrono::high_resolution_clock>
    class Timer
    {
    public:
        constexpr Timer() = default;

        constexpr void start()
        {
            m_begin = Res::now();
        }

        constexpr void reset()
        {
            m_begin = std::chrono::time_point<Res>();
        }

        constexpr T elapsed() const
        {
            return std::chrono::duration_cast<second>(Res::now() - m_begin)
                .count();
        }

    private:
        using second = std::chrono::duration<T>;
        std::chrono::time_point<Res> m_begin;
    };
} // namespace zeus
