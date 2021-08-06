#pragma once

#include "platform.hpp"

#include <string>

namespace zeus
{
    void assert_handler(bool condition,
                        std::string file,
                        int line,
                        std::string message);
} // namespace zeus

#define ZEUS_BUILD_DEBUG
#if defined(ZEUS_BUILD_DEBUG)
#    define ASSERT(condition) \
        zeus::assert_handler(condition, __FILE__, __LINE__, #condition);
#    define ASSERT_MSG(condition, message) \
        zeus::assert_handler(condition, __FILE__, __LINE__, message)
#else
#    define ASSERT(condition)
#    define ASSERT_MSG(condition, message)
#endif

#if defined(ZEUS_ASSERT_IMPL)
#    if defined(ZEUS_PLATFORM_WINDOWS)
#        define WIN32_LEAN_AND_MEAN
#        include <windows.h>
#    endif

#    include <cstdio>
#    include <cstdlib>
#    include <fmt/printf.h>
#    include <stdexcept>

namespace zeus
{
    void print_assert(std::string message)
    {
        fmt::print(stderr, "{}\n", message);

#    if defined(ZEUS_PLATFORM_WINDOWS)
        static constexpr auto max_message_length{16 * 1024};
        char buffer[max_message_length];
        memcpy(buffer, message.c_str(), message.size() + 1);
        strncat_s(buffer, "\n", 3);

        WCHAR wide_buffer[max_message_length] = {0};
        MultiByteToWideChar(
            CP_UTF8, 0, buffer, -1, wide_buffer, sizeof(wide_buffer));
        OutputDebugStringW(wide_buffer);
#    endif
    }

    void assert_handler(bool condition,
                        std::string file,
                        int line,
                        std::string message)
    {
        if (!condition)
        {
            print_assert(fmt::format(
                "error: in file {}({}): {}\n", file, line, message));

#    if defined(ZEUS_PLATFORM_WINDOWS) && !defined(ZEUS_THROW_ASSERT)
            __debugbreak();
#    endif

#    if defined(ZEUS_THROW_ASSERT)
            throw std::runtime_error{"Assert triggered."};
#    else
            std::abort();
#    endif
        }
    }
} // namespace zeus
#endif
