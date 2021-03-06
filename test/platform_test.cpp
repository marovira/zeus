#include <zeus/platform.hpp>

#include <catch2/catch.hpp>
#include <magic_enum.hpp>
#include <string>

#if defined(ZEUS_PLATFORM_WINDOWS)
TEST_CASE("[platform] - template flags: windows", "[zeus]")
{
    using zeus::current_platform;
    REQUIRE(magic_enum::enum_name(current_platform) == "windows");
}
#else
TEST_CASE("[platform] - template flags: linux", "[zeus]")
{
    using zeus::current_platform;
    REQUIRE(magic_enum::enum_name(current_platform) == "linux");
}
#endif

#if defined(ZEUS_BUILD_DEBUG)
TEST_CASE("[platform] - build flags: debug", "[zeus]")
{
    using zeus::current_build;
    REQUIRE(magic_enum::enum_name(current_build) == "debug");
}
#else
TEST_CASE("[platform] - build flags: release", "[zeus]")
{
    using zeus::current_build;
    REQUIRE(magic_enum::enum_name(current_build) == "release");
}
#endif
