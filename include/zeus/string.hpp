#pragma once

#include <algorithm>
#include <array>
#include <cctype>
#include <string>
#include <vector>

namespace zeus
{
    inline constexpr bool is_whitespace(char c)
    {
        std::array matches = {' ', '\f', '\n', '\r', '\t', '\v'};
        return std::any_of(matches.begin(), matches.end(), [c](char opt) {
            return c == opt;
        });
    }

    template<typename DelimFun>
    constexpr std::vector<std::string>
    split(std::string const& str, DelimFun&& is_delim, int max_split)
    {
        if (str.empty())
        {
            return {};
        }

        std::vector<std::string> items;
        std::string cur;
        for (auto ch : str)
        {
            if (is_delim(ch)
                && (max_split == -1 || static_cast<int>(items.size()) < max_split))
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

    inline constexpr std::vector<std::string> split(std::string const& str)
    {
        return split(str, is_whitespace, -1);
    }

    inline constexpr std::vector<std::string> split(std::string const& str, int max_split)
    {
        return split(str, is_whitespace, max_split);
    }

    inline constexpr std::vector<std::string> split(std::string const& str, char delim)
    {
        return split(
            str,
            [delim](char c) {
                return c == delim;
            },
            -1);
    }

    inline constexpr std::vector<std::string>
    split(std::string const& str, char delim, int max_split)
    {
        return split(
            str,
            [delim](char c) {
                return c == delim;
            },
            max_split);
    }

    template<typename TrailingFun>
    constexpr std::string rstrip(std::string const& str, TrailingFun&& is_trailing)
    {
        std::string ret{str};
        ret.erase(std::find_if(ret.rbegin(),
                               ret.rend(),
                               [is_trailing = std::move(is_trailing)](auto c) {
                                   return !is_trailing(c);
                               })
                      .base(),
                  ret.end());
        return ret;
    }

    inline constexpr std::string rstrip(std::string const& str)
    {
        return rstrip(str, is_whitespace);
    }

    template<typename LeadingFun>
    constexpr std::string lstrip(std::string const& str, LeadingFun&& is_leading)
    {
        std::string ret{str};
        ret.erase(ret.begin(),
                  std::find_if(ret.begin(),
                               ret.end(),
                               [is_leading = std::move(is_leading)](auto c) {
                                   return !is_leading(c);
                               }));
        return ret;
    }

    inline constexpr std::string lstrip(std::string const& str)
    {
        return lstrip(str, is_whitespace);
    }

    template<typename LeadingTrailingFun>
    constexpr std::string strip(std::string const& str,
                                LeadingTrailingFun&& is_leading_trailing)
    {
        auto ret = lstrip(str, is_leading_trailing);
        ret      = rstrip(ret, is_leading_trailing);
        return ret;
    }

    inline constexpr std::string strip(std::string const& str)
    {
        return strip(str, is_whitespace);
    }
} // namespace zeus
