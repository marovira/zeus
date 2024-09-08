#include <zeus/platform.hpp>

#include <catch2/catch_test_macros.hpp>
#include <magic_enum.hpp>
#include <string>

#if defined(ZEUS_PLATFORM_WINDOWS)
TEST_CASE("[platform] - template flags: windows", "[zeus]")
{
    using zeus::current_platform;
    STATIC_REQUIRE(magic_enum::enum_name(current_platform) == "windows");
}
#elif defined(ZEUS_PLATFORM_LINUX)
TEST_CASE("[platform] - template flags: linux", "[zeus]")
{
    using zeus::current_platform;
    STATIC_REQUIRE(magic_enum::enum_name(current_platform) == "linux");
}
#elif defined(ZEUS_PLATFORM_APPLE)
TEST_CASE("[platform] - template flags: apple", "[zeus]")
{
    using zeus::current_platform;
    STATIC_REQUIRE(magic_enum::enum_name(current_platform) == "apple");
}
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
