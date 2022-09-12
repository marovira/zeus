#include <zeus/named_type.hpp>

#include <catch2/catch.hpp>

#define MAKE_TEST_TYPE(TypeName, BaseType) \
    using TypeName = zeus::NamedType<BaseType, struct BaseType##_param>

#define MAKE_TEST_TYPE_V(TypeName, BaseType, ...) \
    using TypeName = zeus::NamedType<BaseType, struct BaseType##_param, __VA_ARGS__>

TEMPLATE_TEST_CASE("[NamedType] - get", "[zeus]", int, double)
{
    MAKE_TEST_TYPE(Type, TestType);

    SECTION("Non-const object")
    {
        Type t{1};
        REQUIRE(t.get() == 1);
    }

    SECTION("Const object")
    {
        const Type t{1};
        REQUIRE(t.get() == 1);
    }
}

TEMPLATE_TEST_CASE("[NamedType] - Addable", "[zeus]", int, double)
{
    MAKE_TEST_TYPE_V(Type, TestType, zeus::Addable);

    Type t1{1}, t2{2};

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

    Type t1{1}, t2{2};

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

    Type t1{2}, t2{3};

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

    Type t1{4}, t2{2};

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
