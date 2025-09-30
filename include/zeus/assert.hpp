#pragma once

// NOLINTNEXTLINE(misc-include-cleaner)
#include "platform.hpp" // IWYU pragma: keep

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
    auto assert_handler(bool condition,
                        std::source_location const& loc,
                        std::string message) -> void;
} // namespace zeus

#if defined(ZEUS_BUILD_DEBUG)
#    define ASSERT(condition) \
        zeus::assert_handler(condition, std::source_location::current(), #condition)
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

#    include <array>
#    include <cstdio>
#    include <cstdlib>
#    include <fmt/printf.h>
#    include <stdexcept>

namespace zeus
{
    auto print_assert(std::string message) -> void
    {
        fmt::print(stderr, "{}\n", message);

#    if defined(ZEUS_PLATFORM_WINDOWS)
        static constexpr auto max_message_length{16 * 1'024};
        auto buffer = std::array<char, max_message_length>{};
        memcpy(buffer.data(), message.c_str(), message.size() + 1);
        strncat_s(buffer.data(), buffer.size(), "\n", 3);

        auto wide_buffer = std::array<WCHAR, max_message_length>{};
        MultiByteToWideChar(CP_UTF8,
                            0,
                            buffer.data(),
                            -1,
                            wide_buffer.data(),
                            static_cast<int>(wide_buffer.size() * sizeof(WCHAR)));
        OutputDebugStringW(wide_buffer.data());
#    endif
    }

    auto assert_handler(bool condition,
                        std::source_location const& loc,
                        std::string message) -> void
    {
        if (!condition)
        {
            auto assert_message = fmt::format("error: in file {}({}:{}) \'{}\': {}\n",
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
