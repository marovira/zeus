#include <zeus/concepts.hpp>

#include <catch2/catch_test_macros.hpp>

// NOLINTBEGIN(cppcoreguidelines-use-enum-class)
TEST_CASE("[concepts] - Enum", "[zeus]")
{
    enum Foo
    {
        a = 0
    };

    enum class Bar
    {
        b = 0
    };

    STATIC_REQUIRE(zeus::Enum<Foo>);
    STATIC_REQUIRE(zeus::Enum<Bar>);
    STATIC_REQUIRE_FALSE(zeus::Enum<int>);
}

TEST_CASE("[concepts] - ScopedEnum", "[zeus]")
{
    enum Foo
    {
        a = 0
    };

    enum class Bar
    {
        b = 0
    };

    STATIC_REQUIRE(zeus::ScopedEnum<Bar>);
    STATIC_REQUIRE_FALSE(zeus::ScopedEnum<Foo>);
    STATIC_REQUIRE_FALSE(zeus::ScopedEnum<int>);
}

TEST_CASE("[concepts] - UnsignedEnum", "[zeus]")
{
    enum Foo : int
    {
        a
    };

    enum Bar : unsigned char
    {
        b
    };

    enum class Baz : int
    {
        c
    };

    enum class Bumble : unsigned int
    {
        d
    };

    STATIC_REQUIRE(zeus::UnsignedEnum<Bar>);
    STATIC_REQUIRE_FALSE(zeus::UnsignedEnum<Foo>);

    STATIC_REQUIRE(zeus::UnsignedEnum<Bumble>);
    STATIC_REQUIRE_FALSE(zeus::UnsignedEnum<Baz>);
}

TEST_CASE("[concepts] - UnsignedScopedEnum", "[zeus]")
{
    enum Foo : int
    {
        a
    };

    enum Bar : unsigned char
    {
        b
    };

    enum class Baz : int
    {
        c
    };

    enum class Bumble : unsigned int
    {
        d
    };

    STATIC_REQUIRE(zeus::UnsignedScopedEnum<Bumble>);
    STATIC_REQUIRE_FALSE(zeus::UnsignedScopedEnum<Baz>);
    STATIC_REQUIRE_FALSE(zeus::UnsignedScopedEnum<Bar>);
    STATIC_REQUIRE_FALSE(zeus::UnsignedScopedEnum<Foo>);
}

// NOLINTEND(cppcoreguidelines-use-enum-class)

TEST_CASE("[concepts] - Integral", "[zeus]")
{
    STATIC_REQUIRE(zeus::Integral<signed char>);
    STATIC_REQUIRE(zeus::Integral<short int>);
    STATIC_REQUIRE(zeus::Integral<int>);
    STATIC_REQUIRE(zeus::Integral<long int>);
    STATIC_REQUIRE(zeus::Integral<long long int>);

    STATIC_REQUIRE(zeus::Integral<unsigned char>);
    STATIC_REQUIRE(zeus::Integral<unsigned short int>);
    STATIC_REQUIRE(zeus::Integral<unsigned int>);
    STATIC_REQUIRE(zeus::Integral<unsigned long int>);
    STATIC_REQUIRE(zeus::Integral<unsigned long long int>);

    STATIC_REQUIRE_FALSE(zeus::Integral<float>);
    STATIC_REQUIRE_FALSE(zeus::Integral<double>);
    STATIC_REQUIRE_FALSE(zeus::Integral<long double>);
    STATIC_REQUIRE_FALSE(zeus::Integral<bool>);
}

TEST_CASE("[concepts] - Arithmetic", "[zeus]")
{
    STATIC_REQUIRE(zeus::Integral<signed char>);
    STATIC_REQUIRE(zeus::Integral<short int>);
    STATIC_REQUIRE(zeus::Integral<int>);
    STATIC_REQUIRE(zeus::Integral<long int>);
    STATIC_REQUIRE(zeus::Integral<long long int>);

    STATIC_REQUIRE(zeus::Integral<unsigned char>);
    STATIC_REQUIRE(zeus::Integral<unsigned short int>);
    STATIC_REQUIRE(zeus::Integral<unsigned int>);
    STATIC_REQUIRE(zeus::Integral<unsigned long int>);
    STATIC_REQUIRE(zeus::Integral<unsigned long long int>);

    STATIC_REQUIRE(zeus::Arithmetic<float>);
    STATIC_REQUIRE(zeus::Arithmetic<double>);
    STATIC_REQUIRE(zeus::Arithmetic<long double>);

    STATIC_REQUIRE_FALSE(zeus::Arithmetic<bool>);
}
