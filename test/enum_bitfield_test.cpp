#include <zeus/enum_bitfield.hpp>

#include <catch2/catch.hpp>

enum class Bits
{
    none = 0x0,
    a    = 0x01,
    b    = 0x02,
    c    = 0x04
};

TEST_CASE("[enum_bitfield] - check_flag", "[zeus]")
{
    using namespace magic_enum::bitwise_operators;
    using zeus::check_flag;

    Bits test = Bits::a | Bits::b;

    REQUIRE(check_flag(test, Bits::a));
    REQUIRE_FALSE(check_flag(test, Bits::c));
}
