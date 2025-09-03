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
        apple,
    };

    enum class ApplePlatform
    {
        arm64,  // Denotes Apple Silicon CPU.
        x86_64, // Denotes Intel CPU.
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
#    define ZEUS_PLATFORM_APPLE
    static constexpr Platform current_platform{Platform::apple};
#    if defined(__arm64__) || defined(__arm64)
#        define ZEUS_PLATFORM_APPLE_ARM64
    static constexpr ApplePlatform current_apple_platform{ApplePlatform::arm64};
#    elif defined(__x86_64) || defined(__x86_64__)
#        define ZEUS_PLATFORM_APPLE_X86_64
    static constexpr ApplePlatform current_apple_platform{ApplePlatform::x86_64};
#    else
#        error "Unknown Apple platform detected"
#    endif
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
