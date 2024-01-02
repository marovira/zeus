#pragma once

#include "concepts.hpp"

#include <array>
#include <string>
#include <vector>

namespace zeus
{
    template<typename T>
    struct IsContiguousContainer : std::false_type
    {};

    template<typename T>
    struct IsContiguousContainer<std::vector<T>> : std::true_type
    {};

    template<typename T, std::size_t N>
    struct IsContiguousContainer<std::array<T, N>> : std::true_type
    {};

    template<typename T>
    struct IsContiguousContainer<std::basic_string<T>> : std::true_type
    {};

    template<typename T>
    concept ContiguousContainer = IsContiguousContainer<T>::value;
} // namespace zeus
