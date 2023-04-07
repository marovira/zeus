#pragma once

#include "concepts.hpp"

#include <algorithm>
#include <cctype>
#include <vector>

namespace zeus
{
    // template<typename T, typename U>
    // requires is_string<T>
    // std::vector<T> split(T const& str, U delim)
    //{
    //     static_assert(std::is_same<typename T::value_type, U>::value);
    //     std::vector<T> items;
    //     T cur;
    //     for (auto ch : str)
    //     {
    //         if (ch == delim)
    //         {
    //             items.push_back(cur);
    //             cur.clear();
    //             continue;
    //         }

    //        cur.push_back(ch);
    //    }
    //    items.push_back(cur);

    //    return items;
    //}

    // template<typename T>
    // requires is_string<T>
    // std::vector<T> split(T const& str, T const& delim)
    //{
    //     if (delim.size() > str)
    //     {
    //         return {str};
    //     }

    //    std::vector<T> items;
    //    std::size_t prev_item{0};
    //    for (std::size_t i{0}; i < str.size() - delim.size(); ++i)
    //    {
    //        auto substr = str.substr(i, delim.size());
    //        if (substr == delim)
    //        {
    //            auto item = str.substr(prev_item, prev_item - i);
    //            items.push_back(item);
    //            continue;
    //        }
    //    }

    //    return items;
    //}

    // template<typename T>
    // requires is_string<T>
    // void trim(T& str)
    //{
    //     // Trim leading whitespace.
    //     str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](auto ch) {
    //                   return !std::isspace(ch);
    //               }));

    //    // Trim trailing whitespace.
    //    str.erase(std::find_if(str.rbegin(),
    //                           str.rend(),
    //                           [](auto ch) {
    //                               return !std::isspace(ch);
    //                           })
    //                  .base(),
    //              str.end());
    //}

    // template<typename T>
    // requires is_string<T>
    // T trim(T const& str)
    //{
    //     T ret{str};
    //     trim(ret);
    //     return ret;
    // }
} // namespace zeus
