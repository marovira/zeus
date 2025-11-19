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

TEST_CASE("[concepts] - IntegralType", "[zeus]")
{
    STATIC_REQUIRE(zeus::IntegralType<char>);
    STATIC_REQUIRE(zeus::IntegralType<char8_t>);
    STATIC_REQUIRE(zeus::IntegralType<char16_t>);
    STATIC_REQUIRE(zeus::IntegralType<char32_t>);
    STATIC_REQUIRE(zeus::IntegralType<wchar_t>);
    STATIC_REQUIRE(zeus::IntegralType<short>);
    STATIC_REQUIRE(zeus::IntegralType<int>);
    STATIC_REQUIRE(zeus::IntegralType<long>);
    STATIC_REQUIRE(zeus::IntegralType<long long>);

    STATIC_REQUIRE_FALSE(zeus::IntegralType<float>);
    STATIC_REQUIRE_FALSE(zeus::IntegralType<double>);
    STATIC_REQUIRE_FALSE(zeus::IntegralType<long double>);
    STATIC_REQUIRE_FALSE(zeus::IntegralType<bool>);
}

TEST_CASE("[concepts] - ArithmeticType", "[zeus]")
{
    STATIC_REQUIRE(zeus::ArithmeticType<char>);
    STATIC_REQUIRE(zeus::ArithmeticType<char8_t>);
    STATIC_REQUIRE(zeus::ArithmeticType<char16_t>);
    STATIC_REQUIRE(zeus::ArithmeticType<char32_t>);
    STATIC_REQUIRE(zeus::ArithmeticType<wchar_t>);
    STATIC_REQUIRE(zeus::ArithmeticType<short>);
    STATIC_REQUIRE(zeus::ArithmeticType<int>);
    STATIC_REQUIRE(zeus::ArithmeticType<long>);
    STATIC_REQUIRE(zeus::ArithmeticType<long long>);
    STATIC_REQUIRE(zeus::ArithmeticType<float>);
    STATIC_REQUIRE(zeus::ArithmeticType<double>);
    STATIC_REQUIRE(zeus::ArithmeticType<long double>);

    STATIC_REQUIRE_FALSE(zeus::ArithmeticType<bool>);
}
