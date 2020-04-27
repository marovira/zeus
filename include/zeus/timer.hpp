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
            _begin = Res::now();
        }

        constexpr void reset()
        {
            _begin = std::chrono::time_point<Res>();
        }

        constexpr T elapsed() const
        {
            return std::chrono::duration_cast<second>(Res::now() - _begin)
                .count();
        }

    private:
        using second = std::chrono::duration<T>;
        std::chrono::time_point<Res> _begin;
    };
} // namespace zeus
