#pragma once

#include "platform.hpp"

#include <array>
#include <source_location>
#include <string>

#if defined(ZEUS_ENABLE_TESTING_MACROS)
#    define ZEUS_BUILD_DEBUG
#    define ZEUS_THROW_ASSERT
#    define ZEUS_NO_DEBUG_BREAK_ASSERT
#    define ZEUS_NO_ASSERT_PRINT
#endif

namespace zeus
{
    void
    assert_handler(bool condition, std::source_location const& loc, std::string message);
} // namespace zeus

#if defined(ZEUS_BUILD_DEBUG)
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#    define ASSERT(condition) \
        zeus::assert_handler(condition, std::source_location::current(), #condition)
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#    define ASSERT_MSG(condition, message) \
        zeus::assert_handler(condition, std::source_location::current(), message)
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
        static constexpr auto max_message_length{16 * 1'024};
        std::array<char, max_message_length> buffer{};
        memcpy(buffer.data(), message.c_str(), message.size() + 1);
        strncat_s(buffer.data(), buffer.size(), "\n", 3);

        std::array<WCHAR, max_message_length> wide_buffer{};
        MultiByteToWideChar(CP_UTF8,
                            0,
                            buffer.data(),
                            -1,
                            wide_buffer.data(),
                            static_cast<int>(wide_buffer.size() * sizeof(WCHAR)));
        OutputDebugStringW(wide_buffer.data());
#    endif
    }

    void
    assert_handler(bool condition, std::source_location const& loc, std::string message)
    {
        if (!condition)
        {
            std::string assert_message =
                fmt::format("error: in file {}({}:{}) \'{}\': {}\n",
                            loc.file_name(),
                            loc.line(),
                            loc.column(),
                            loc.function_name(),
                            message);

#    if !defined(ZEUS_NO_ASSERT_PRINT)
            print_assert(assert_message);
#    endif

#    if defined(ZEUS_PLATFORM_WINDOWS) && !defined(ZEUS_NO_DEBUG_BREAK_ASSERT)
            // Exceptions don't always trigger a break in program execution (and
            // if they do they sometimes don't stop where you want), so I'm
            // leaving this here so the break happens.
            __debugbreak();
#    endif

#    if defined(ZEUS_THROW_ASSERT)
            throw std::runtime_error{assert_message.c_str()};
#    else
            std::abort();
#    endif
        }
    }
} // namespace zeus
#endif
