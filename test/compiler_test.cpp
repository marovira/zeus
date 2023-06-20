#include <zeus/compiler.hpp>

#include <catch2/catch_test_macros.hpp>
#include <magic_enum.hpp>
#include <string>

#if defined(ZEUS_COMPILER_MSVC)
TEST_CASE("[compiler] - compiler flags: msvc", "[zeus]")
{
    using zeus::current_compiler;
    STATIC_REQUIRE(magic_enum::enum_name(current_compiler) == "msvc");
}
#elif defined(ZEUS_COMPILER_GCC)
TEST_CASE("[compiler] - compiler flags: gcc", "[zeus]")
{
    using zeus::current_compiler;
    STATIC_REQUIRE(magic_enum::enum_name(current_compiler) == "gcc");
}
#elif defined(ZEUS_COMPILER_CLANG)
TEST_CASE("[compiler] - compiler flags: clang", "[zeus]")
{
    using zeus::current_compiler;
    STATIC_REQUIRE(magic_enum::enum_name(current_compiler) == "clang");
}
#endif
