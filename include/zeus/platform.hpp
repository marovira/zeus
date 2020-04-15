#pragma once

#if defined(linux)
#    undef linux
#endif

namespace zeus
{
    enum class platform
    {
        windows = 0,
        linux
    };

    enum class build_type
    {
        debug = 0,
        release
    };

#if defined(_WIN32) || defined(_WIN64)
#    define ZEUS_PLATFORM_WINDOWS
    static constexpr platform current_platform{platform::windows};
#elif defined(__APPLE__)
#    error "Support for Apple is deprecated"
#elif defined(__linux__)
#    define ZEUS_PLATFORM_LINUX
    static constexpr platform current_platform{platform::linux};
#endif

#if defined(_DEBUG) || defined(DEBUG) || defined(__DEBUG__)
#    define ZEUS_BUILD_DEBUG
    static constexpr build_type current_build{build_type::debug};
#else
#    define ZEUS_BUILD_RELEASE
    static constexpr build_type current_build{build_type::release};
#endif

} // namespace zeus
