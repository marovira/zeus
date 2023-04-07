#pragma once

#include "string.hpp"

#include <filesystem>
#include <fmt/printf.h>
#include <fstream>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

namespace zeus
{
    class ConfigParser
    {
    public:
        class Section
        {
        public:
            void insert(std::string const& key, std::string const& value)
            {
                m_keys.insert({key, value});
            }

            std::vector<std::string> keys() const
            {
                std::vector<std::string> keys;
                std::transform(m_keys.begin(),
                               m_keys.end(),
                               std::back_inserter(keys),
                               [](auto pair) {
                                   return pair.first;
                               });
                return keys;
            }

            bool exists(std::string const& key) const
            {
                return m_keys.find(key) != m_keys.end();
            }

            std::string& operator[](std::string const& key)
            {
                return m_keys.at(key);
            }

            std::string const& operator[](std::string const& key) const
            {
                return m_keys.at(key);
            }

            template<typename T>
            T value_as(std::string const& key)
            {
                static_assert(std::is_same_v<T, int> || std::is_same_v<T, float>
                                  || std::is_same_v<T, bool>,
                              "error: type is not implemented");

                std::string val = m_keys.at(key);

                if constexpr (std::is_same<T, int>::value)
                {
                    return std::stoi(val);
                }
                else if constexpr (std::is_same<T, float>::value)
                {
                    return std::stof(val);
                }
                else if constexpr (std::is_same<T, bool>::value)
                {
                    std::transform(val.begin(), val.end(), val.begin(), [](auto ch) {
                        return static_cast<decltype(ch)>(std::tolower(ch));
                    });
                    if (val == "yes" || val == "on" || val == "true" || val == "1")
                    {
                        return true;
                    }
                    else if (val == "no" || val == "off" || val == "false" || val == "0")
                    {
                        return false;
                    }

                    auto msg =
                        fmt::format("error: invalid value for bool type. Expected one of "
                                    "on/off, yes/no, true/false, 0/1, but received {}",
                                    val);
                    throw std::runtime_error{msg.c_str()};
                }
            }

        private:
            std::map<std::string, std::string> m_keys;
        };

        void insert(std::string const& name, Section const& s)
        {
            m_sections.insert({name, s});
        }

        std::vector<std::string> sections() const
        {
            std::vector<std::string> sections;
            std::transform(m_sections.begin(),
                           m_sections.end(),
                           std::back_inserter(sections),
                           [](auto const& pair) {
                               return pair.first;
                           });

            return sections;
        }

        bool exists(std::string const& section) const
        {
            return m_sections.find(section) != m_sections.end();
        }

        Section& operator[](std::string const& section)
        {
            return m_sections.at(section);
        }

        Section const& operator[](std::string const& section) const
        {
            return m_sections.at(section);
        }

        bool read(std::string const& filename)
        {
            namespace fs = std::filesystem;

            fs::path file_path{filename};
            file_path = fs::absolute(file_path).make_preferred();

            if (!fs::exists(file_path))
            {
                return false;
            }

            std::ifstream stream{file_path.string()};
            if (!stream)
            {
                return false;
            }

            std::string line;
            std::string current_section;
            while (std::getline(stream, line))
            {
                if (line.empty())
                {
                    continue;
                }

                // Strip out leading and trailing whitespace.
                line = strip(line);

                if (line[0] == '#' || line[0] == ';')
                {
                    continue;
                }

                // Section header.
                if (line[0] == '[')
                {
                    std::size_t header_len = line.size() - 2;
                    std::string header     = line.substr(1, header_len);

                    m_sections.insert({header, Section{}});
                    current_section = header;
                    continue;
                }

                if (line.find(":") != std::string::npos
                    || line.find("=") != std::string::npos)
                {
                    std::size_t delim_pos{0};
                    if (auto pos = line.find(":"); pos != std::string::npos)
                    {
                        delim_pos = pos;
                    }
                    else
                    {
                        delim_pos = line.find("=");
                    }

                    // Split the string: the key is the stuff before the = and the
                    // value is whatever is left. Remember to
                    // trim whitespace
                    std::string key   = line.substr(0, delim_pos);
                    std::string value = line.substr(delim_pos + 1);

                    key   = strip(key);
                    value = strip(value);
                    std::transform(key.begin(), key.end(), key.begin(), [](auto ch) {
                        return static_cast<decltype(ch)>(std::tolower(ch));
                    });
                    m_sections.at(current_section).insert(key, value);
                    continue;
                }
            }

            return true;
        }

    private:
        std::map<std::string, Section> m_sections;
    };
} // namespace zeus
