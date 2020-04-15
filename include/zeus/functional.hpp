#pragma once

namespace zeus
{
    template<typename ForwardIt, typename T>
    void iota(ForwardIt first, ForwardIt last, T value, T step)
    {
        while (first != last)
        {
            *first++ = value;
            value += step;
        }
    }
} // namespace zeus
