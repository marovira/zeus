#include <zeus/platform.hpp>

#include <catch2/catch_test_macros.hpp>
#include <magic_enum/magic_enum.hpp>

#if defined(ZEUS_PLATFORM_WINDOWS)
TEST_CASE("[platform] - platform flags: windows", "[zeus]")
{
    using zeus::current_platform;
    STATIC_REQUIRE(magic_enum::enum_name(current_platform) == "windows");
}
#elif defined(ZEUS_PLATFORM_APPLE)
TEST_CASE("[platform] - platform flags: apple", "[zeus]")
{
    using zeus::current_platform;
    STATIC_REQUIRE(magic_enum::enum_name(current_platform) == "apple");
}
#elif defined(ZEUS_PLATFORM_LINUX)
TEST_CASE("[platform] - platform flags: linux", "[zeus]")
{
    using zeus::current_platform;
    STATIC_REQUIRE(magic_enum::enum_name(current_platform) == "linux");
}
#endif

#if defined(ZEUS_PLATFORM_APPLE)
#    if defined(ZEUS_PLATFORM_APPLE_ARM64)
TEST_CASE("[platform] - apple flags: arm64", "[zeus]")
{
    using zeus::current_apple_platform;
    STATIC_REQUIRE(magic_enum::enum_name(current_apple_platform) == "arm64");
}
#    elif defined(ZEUS_PLATFORM_APPLE_X86_64)
TEST_CASE("[platform] - apple flags: x86_64", "[zeus]")
{
    using zeus::current_apple_platform;
    STATIC_REQUIRE(magic_enum::enum_name(current_apple_platform) == "x86_64");
}
#    endif
#endif

#if defined(ZEUS_BUILD_DEBUG)
TEST_CASE("[platform] - build flags: debug", "[zeus]")
{
    using zeus::current_build;
    STATIC_REQUIRE(magic_enum::enum_name(current_build) == "debug");
}
#else
TEST_CASE("[platform] - build flags: release", "[zeus]")
{
    using zeus::current_build;
    STATIC_REQUIRE(magic_enum::enum_name(current_build) == "release");
}
#endif
