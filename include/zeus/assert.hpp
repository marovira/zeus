#pragma once

#include "platform.hpp"

#include <string>

namespace zeus
{
    void assert_handler(bool condition,
                        std::string file,
                        int line,
                        std::string message);

#define ZEUS_BUILD_DEBUG
#if defined(ZEUS_BUILD_DEBUG)
#    define ASSERT(condition) \
        assert_handler(condition, __FILE__, __LINE__, #condition);
#    define ASSERT_MSG(condition, message) \
        assert_handler(condition, __FILE__, __LINE__, message)
#else
#    define ASSERT(condition)
#    define ASSERT_MSG(condition, message)
#endif
} // namespace zeus

#if defined(ZEUS_ASSERT_IMPL)
#    if defined(ZEUS_PLATFORM_WINDOWS)
#        define WIN32_LEAN_AND_MEAN
#        include <windows.h>
#    endif

#    include <cstdio>
#    include <cstdlib>
#    include <fmt/printf.h>

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

#    if defined(ZEUS_PLATFORM_WINDOWS)
            __debugbreak();
#    endif
            std::abort();
        }
    }
} // namespace zeus
#endif
