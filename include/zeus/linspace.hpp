#pragma once

#include "concepts.hpp"

#include <concepts>
#include <stdexcept>
#include <vector>

// A C++ version of NumPY's linspace.
// Adapted from NumCPP
// https://github.com/dpilger26/NumCpp

namespace zeus
{
    template<std::floating_point T, UnsignedIntegral U>
    std::vector<T> linspace(T start, T stop, U num_steps, bool include_end_point)
    {
        using RetType = std::vector<T>;

        if (num_steps == 0)
        {
            return {};
        }

        if (num_steps == 1)
        {
            return RetType{start};
        }

        if (stop <= start)
        {
            throw std::runtime_error{
                "error: stop value must be greater than the start value"};
        }

        if (include_end_point)
        {
            if (num_steps == 2)
            {
                return RetType{start, stop};
            }

            RetType return_array(num_steps);
            return_array.front() = start;
            return_array.back()  = stop;

            const auto step = (stop - start) / static_cast<T>(num_steps - 1);
            for (U i{1}; i < num_steps - 1; ++i)
            {
                return_array[i] = start + static_cast<T>(i) * step;
            }

            return return_array;
        }

        if (num_steps == 2)
        {
            const auto step = (stop - start) / static_cast<T>(num_steps);
            return RetType{start, start + step};
        }

        RetType return_array(num_steps);
        return_array.front() = start;

        const auto step = (stop - start) / static_cast<T>(num_steps);
        for (U i{1}; i < num_steps; ++i)
        {
            return_array[i] = start + static_cast<T>(i) * step;
        }

        return return_array;
    }

    template<std::floating_point T, UnsignedIntegral U>
    std::vector<T> linspace(T start, T stop, U num_steps)
    {
        return linspace<T, U>(start, stop, num_steps, true);
    }
} // namespace zeus
