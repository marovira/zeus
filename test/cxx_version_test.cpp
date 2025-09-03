#include <zeus/cxx_version.hpp>

#include <catch2/catch_test_macros.hpp>
#include <magic_enum/magic_enum.hpp>

TEST_CASE("[cxx_version] - C++ version flags: 20", "[zeus]")
{
    using zeus::current_cxx_version;
    STATIC_REQUIRE(magic_enum::enum_name(current_cxx_version) == "std_20");
}

#if ZEUS_CXX_VERSION == ZEUS_CXX_23
TEST_CASE("[cxx_version] - C++ version flags: 23", "[zeus]")
{
    using zeus::current_cxx_version;
    STATIC_REQUIRE(magic_enum::enum_name(current_cxx_version) == "std_23");
}
#endif
