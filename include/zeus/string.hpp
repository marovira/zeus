#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace zeus
{
    inline constexpr bool is_whitespace(char c)
    {
        std::array matches = {' ', '\f', '\n', '\r', '\t', '\v'};
        return std::ranges::any_of(matches, [c](char opt) {
            return c == opt;
        });
    }

    template<typename T>
    concept DelimiterFunctor = requires(T t, char c) {
        { t(c) } -> std::same_as<bool>;
    };

    template<DelimiterFunctor T>
    constexpr std::vector<std::string>
    split(std::string const& str, T is_delim, int max_split)
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
                && (max_split == -1 || std::cmp_less(items.size(), max_split)))
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

    template<DelimiterFunctor TrailingFun>
    constexpr std::string rstrip(std::string const& str, TrailingFun is_trailing)
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

    template<DelimiterFunctor LeadingFun>
    constexpr std::string lstrip(std::string const& str, LeadingFun is_leading)
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

    template<DelimiterFunctor LeadingTrailingFun>
    constexpr std::string strip(std::string const& str,
                                LeadingTrailingFun is_leading_trailing)
    {
        auto ret = lstrip(str, is_leading_trailing);
        ret      = rstrip(ret, is_leading_trailing);
        return ret;
    }

    inline constexpr std::string strip(std::string const& str)
    {
        return strip(str, is_whitespace);
    }

    inline constexpr std::vector<std::string> split_lines(std::string const& str,
                                                          bool keep_line_breaks)
    {
        if (str.empty())
        {
            return {};
        }

        std::vector<std::string> lines;
        std::string line;
        bool check_crlf{false};
        for (std::size_t i{0}; i < str.size(); ++i)
        {
            if (str[i] == '\r' && !check_crlf)
            {
                check_crlf = true;
                continue;
            }

            if (str[i] == '\n')
            {
                if (keep_line_breaks)
                {
                    if (check_crlf)
                    {
                        line.push_back('\r');
                    }

                    line.push_back(str[i]);
                }

                lines.push_back(line);
                line.clear();
                check_crlf = false;
                continue;
            }

            if (check_crlf)
            {
                // Split off the string, since we know for sure that we didn't see a \r\n
                // sequence.
                if (keep_line_breaks)
                {
                    line.push_back('\r');
                }

                lines.push_back(line);
                line.clear();
                check_crlf = false;

                // Handle the case where we have consecutive \r symbols.
                if (str[i] == '\r')
                {
                    check_crlf = true;
                    continue;
                }
            }

            line.push_back(str[i]);
        }

        // Don't add an empty line if the final character in the string is a newline.
        if (line.empty() && (str.back() == '\n' || (str.back() == '\r' && !check_crlf)))
        {
            return lines;
        }

        // Ensure the final line keeps its carriage return if requested.
        if (check_crlf && keep_line_breaks)
        {
            line.push_back('\r');
        }

        lines.push_back(line);
        return lines;
    }

    inline constexpr std::vector<std::string> split_lines(std::string const& str)
    {
        return split_lines(str, false);
    }
} // namespace zeus
