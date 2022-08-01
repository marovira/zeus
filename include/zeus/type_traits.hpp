#pragma once

#include <type_traits>

namespace zeus
{
    template<typename T, typename... Args>
    struct Contains : public std::bool_constant<(std::is_same<T, Args>{} || ...)>
    {};
} // namespace zeus
