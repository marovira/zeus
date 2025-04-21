#pragma once

#if defined(linux)
#    undef linux
#endif

namespace zeus
{
    enum class Platform
    {
        windows = 0,
        linux,
    };

    enum class BuildType
    {
        debug = 0,
        release
    };

#if defined(_WIN32) || defined(_WIN64)
#    define ZEUS_PLATFORM_WINDOWS
    static constexpr Platform current_platform{Platform::windows};
#elif defined(__APPLE__)
#    error "Zeus does not support Apple platforms"
#elif defined(__linux__)
#    define ZEUS_PLATFORM_LINUX
    static constexpr Platform current_platform{Platform::linux};
#endif

#if defined(_DEBUG) || defined(DEBUG) || defined(__DEBUG__)
#    define ZEUS_BUILD_DEBUG
    static constexpr BuildType current_build{BuildType::debug};
#else
#    define ZEUS_BUILD_RELEASE
    static constexpr BuildType current_build{BuildType::release};
#endif
} // namespace zeus
