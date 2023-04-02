#pragma once

#include "concepts.hpp"

#include <algorithm>
#include <cctype>
#include <vector>

namespace zeus
{
    template<typename T, typename U>
    requires is_string<T>
    std::vector<T> split(T const& str, U delim)
    {
        static_assert(std::is_same<typename T::value_type, U>::value);
        std::vector<T> items;
        T cur;
        for (auto ch : str)
        {
            if (ch == delim)
            {
                items.push_back(cur);
                cur.clear();
                continue;
            }

            cur.push_back(ch);
        }
        items.push_back(cur);

        return items;
    }

    template<typename T>
    requires is_string<T>
    void trim(T& str)
    {
        // Trim leading whitespace.
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](auto ch) {
                      return !std::isspace(ch);
                  }));

        // Trim trailing whitespace.
        str.erase(std::find_if(str.rbegin(),
                               str.rend(),
                               [](auto ch) {
                                   return !std::isspace(ch);
                               })
                      .base(),
                  str.end());
    }

    template<typename T>
    requires is_string<T>
    T trim(T const& str)
    {
        T ret{str};
        trim(ret);
        return ret;
    }
} // namespace zeus
