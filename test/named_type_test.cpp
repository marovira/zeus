#include <zeus/named_type.hpp>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

// NOLINTBEGIN(bugprone-macro-parentheses)
#define MAKE_TEST_TYPE(TypeName, BaseType) \
    using TypeName = zeus::NamedType<BaseType, struct BaseType##_param>

#define MAKE_TEST_TYPE_V(TypeName, BaseType, ...) \
    using TypeName = zeus::NamedType<BaseType, struct BaseType##_param, __VA_ARGS__>

// NOLINTEND(bugprone-macro-parentheses)

TEMPLATE_TEST_CASE("[NamedType] - get", "[zeus]", int, double)
{
    MAKE_TEST_TYPE(Type, TestType);

    SECTION("Non-const object")
    {
        auto t = Type{1};
        REQUIRE(t.get() == 1);
    }

    SECTION("Const object")
    {
        const auto t = Type{1};
        REQUIRE(t.get() == 1);
    }
}

TEMPLATE_TEST_CASE("[NamedType] - Addable", "[zeus]", int, double)
{
    MAKE_TEST_TYPE_V(Type, TestType, zeus::Addable);

    auto t1 = Type{1};
    const auto t2 = Type{2};

    SECTION("Operator +=")
    {
        t1 += t2;
        REQUIRE(t1.get() == 3);
    }

    SECTION("Operator +")
    {
        auto t3 = t1 + t2;
        REQUIRE(t3.get() == 3);
    }
}

TEMPLATE_TEST_CASE("[NamedType] - Subtractable", "[zeus]", int, double)
{
    MAKE_TEST_TYPE_V(Type, TestType, zeus::Subtractable);

    const auto t1 = Type{1};
    auto t2 = Type{2};

    SECTION("Operator -=")
    {
        t2 -= t1;
        REQUIRE(t2.get() == 1);
    }

    SECTION("Operator -")
    {
        auto t3 = t2 - t1;
        REQUIRE(t3.get() == 1);
    }
}

TEMPLATE_TEST_CASE("[NamedType] - Multiplicable", "[zeus]", int, double)
{
    MAKE_TEST_TYPE_V(Type, TestType, zeus::Multiplicable);

    auto t1 = Type{2};
    const auto t2 = Type{3};

    SECTION("Operator *=")
    {
        t1 *= t2;
        REQUIRE(t1.get() == 6);
    }

    SECTION("Operator *")
    {
        auto t3 = t1 * t2;
        REQUIRE(t3.get() == 6);
    }
}

TEMPLATE_TEST_CASE("[NamedType] - Divisible", "[zeus]", int, double)
{
    MAKE_TEST_TYPE_V(Type, TestType, zeus::Divisible);

    auto t1 = Type{4};
    const auto t2 = Type{2};

    SECTION("Operator /=")
    {
        t1 /= t2;
        REQUIRE(t1.get() == 2);
    }

    SECTION("Operator /")
    {
        auto t3 = t1 / t2;
        REQUIRE(t3.get() == 2);
    }
}
