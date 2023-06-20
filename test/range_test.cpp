#include <zeus/range.hpp>

#include <catch2/catch_template_test_macros.hpp>

#include <algorithm>

using zeus::Range;
using zeus::range;

TEMPLATE_TEST_CASE("[Range] - constructors", "[zeus]", int, float)
{
    SECTION("end")
    {
        SECTION("Runtime")
        {
            Range<TestType> r{10};
            REQUIRE(r.size() == 10);
        }

        SECTION("Compile-time")
        {
            static constexpr auto empty = []() {
                Range<TestType> r{10};
                return r.size();
            }();
            STATIC_REQUIRE(empty == 10);
        }
    }

    SECTION("begin + end")
    {
        SECTION("Runtime")
        {
            Range<TestType> r{0, 10};
            REQUIRE(r.size() == 10);
        }

        SECTION("Compile-time")
        {
            static constexpr auto size = []() {
                Range<TestType> r{0, 10};
                return r.size();
            }();
            STATIC_REQUIRE(size == 10);
        }
    }

    SECTION("begin + end + step")
    {
        SECTION("Runtime")
        {
            Range<TestType> r{0, 10, 1};
            REQUIRE(r.size() == 10);
        }

        SECTION("Compile-time")
        {
            static constexpr auto size = []() {
                Range<TestType> r{0, 10, 1};
                return r.size();
            }();
            STATIC_REQUIRE(size == 10);
        }
    }

    SECTION("Invalid step")
    {
        REQUIRE_THROWS(Range<TestType>{0, 10, 0});
    }
}

TEMPLATE_TEST_CASE("[Range] - size", "[zeus]", int, float)
{
    SECTION("Empty range")
    {
        SECTION("Runtime")
        {
            Range<TestType> r{0};
            REQUIRE(r.size() == 0);
        }

        SECTION("Compile-time")
        {
            static constexpr auto empty = []() {
                Range<TestType> r{0};
                return r.size();
            }();
            STATIC_REQUIRE(empty == 0);
        }
    }

    SECTION("Positive range, unit step")
    {
        SECTION("Runtime")
        {
            Range<TestType> r{10};
            REQUIRE(r.size() == 10);
        }

        SECTION("Compile-time")
        {
            static constexpr auto size = []() {
                Range<TestType> r{10};
                return r.size();
            }();
            STATIC_REQUIRE(size == 10);
        }
    }

    SECTION("Negative range, unit step")
    {
        SECTION("Runtime")
        {
            Range<TestType> r{-10, 0};
            REQUIRE(r.size() == 10);
        }

        SECTION("Compile-time")
        {
            static constexpr auto size = []() {
                Range<TestType> r{-10, 0};
                return r.size();
            }();
            STATIC_REQUIRE(size == 10);
        }
    }

    SECTION("Positive range, positive step")
    {
        SECTION("Runtime")
        {
            Range<TestType> r{0, 10, 2};
            REQUIRE(r.size() == 5);
        }

        SECTION("Compile-time")
        {
            static constexpr auto size = []() {
                Range<TestType> r{0, 10, 2};
                return r.size();
            }();
            STATIC_REQUIRE(size == 5);
        }
    }

    SECTION("Positive range, negative step")
    {
        SECTION("Runtime")
        {
            Range<TestType> r{10, 0, -2};
            REQUIRE(r.size() == 5);
        }

        SECTION("Compile-time")
        {
            static constexpr auto size = []() {
                Range<TestType> r{10, 0, -2};
                return r.size();
            }();
            STATIC_REQUIRE(size == 5);
        }
    }

    SECTION("Negative range, positive step")
    {
        SECTION("Runtime")
        {
            Range<TestType> r{-10, 0, 2};
            REQUIRE(r.size() == 5);
        }

        SECTION("Compile-time")
        {
            static constexpr auto size = []() {
                Range<TestType> r{-10, 0, 2};
                return r.size();
            }();
            STATIC_REQUIRE(size == 5);
        }
    }

    SECTION("Negative range, negative step")
    {
        SECTION("Runtime")
        {
            Range<TestType> r{0, -10, -2};
            REQUIRE(r.size() == 5);
        }

        SECTION("Compile-time")
        {
            static constexpr auto size = []() {
                Range<TestType> r{0, -10, -2};
                return r.size();
            }();
            STATIC_REQUIRE(size == 5);
        }
    }
}

TEMPLATE_TEST_CASE("[Range] - empty", "[zeus]", int, float)
{
    SECTION("Empty range")
    {
        SECTION("Runtime")
        {
            Range<TestType> r{0};
            REQUIRE(r.empty());
        }

        SECTION("Compile-time")
        {
            static constexpr auto empty = []() {
                Range<TestType> r{0};
                return r.empty();
            }();
            STATIC_REQUIRE(empty);
        }
    }

    SECTION("Non-empty range")
    {
        SECTION("Runtime")
        {
            Range<TestType> r{10};
            REQUIRE_FALSE(r.empty());
        }

        SECTION("Compile-time")
        {
            static constexpr auto empty = []() {
                Range<TestType> r{10};
                return r.empty();
            }();
            STATIC_REQUIRE_FALSE(empty);
        }
    }
}

TEMPLATE_TEST_CASE("[Range::Iterator] - constructor", "[zeus]", int, float)
{
    using It = typename Range<TestType>::Iterator;

    SECTION("Runtime")
    {
        It it{0, 1};
        REQUIRE(*it == 0);
    }

    SECTION("Compile-time")
    {
        static constexpr auto val = []() {
            It it{0, 1};
            return *it;
        }();
        STATIC_REQUIRE(val == 0);
    }
}

TEMPLATE_TEST_CASE("[Range::Iterator] - operator++", "[zeus]", int, float)
{
    using It = typename Range<TestType>::Iterator;

    SECTION("Unit step")
    {
        SECTION("Runtime")
        {
            It it{0, 1};
            ++it;
            REQUIRE(*it == 1);
        }

        SECTION("Compile-time")
        {
            static constexpr auto val = []() {
                It it{0, 1};
                ++it;
                return *it;
            }();

            STATIC_REQUIRE(val == 1);
        }
    }

    SECTION("Positive step")
    {
        SECTION("Runtime")
        {
            It it{0, 2};
            ++it;
            REQUIRE(*it == 2);
        }

        SECTION("Compile-time")
        {
            static constexpr auto val = []() {
                It it{0, 2};
                ++it;
                return *it;
            }();

            STATIC_REQUIRE(val == 2);
        }
    }

    SECTION("Negative step")
    {
        SECTION("Runtime")
        {
            It it{0, -2};
            ++it;
            REQUIRE(*it == -2);
        }

        SECTION("Compile-time")
        {
            static constexpr auto val = []() {
                It it{0, -2};
                ++it;
                return *it;
            }();

            STATIC_REQUIRE(val == -2);
        }
    }
}

TEMPLATE_TEST_CASE("[Range::Iterator] - operator==", "[zeus]", int, float)
{
    using It = typename Range<TestType>::Iterator;

    SECTION("Equal iterators")
    {
        SECTION("Runtime")
        {
            It a{0, 1};
            It b{0, 2};
            REQUIRE(a == b);
        }

        SECTION("Compile-time")
        {
            static constexpr auto val = []() {
                It a{0, 1};
                It b{0, 2};
                return a == b;
            }();

            STATIC_REQUIRE(val);
        }
    }

    SECTION("Non-equal iterators")
    {
        SECTION("Runtime")
        {
            It a{0, 1};
            It b{1, 2};
            REQUIRE_FALSE(a == b);
        }

        SECTION("Compile-time")
        {
            static constexpr auto val = []() {
                It a{0, 1};
                It b{1, 2};
                return a == b;
            }();

            STATIC_REQUIRE_FALSE(val);
        }
    }
}

TEMPLATE_TEST_CASE("[Range::Iterator] - operator!=", "[zeus]", int, float)
{
    using It = typename Range<TestType>::Iterator;

    SECTION("Equal iterators")
    {
        SECTION("Runtime")
        {
            It a{0, 1};
            It b{0, 2};
            REQUIRE_FALSE(a != b);
        }

        SECTION("Compile-time")
        {
            static constexpr auto val = []() {
                It a{0, 1};
                It b{0, 2};
                return a != b;
            }();

            STATIC_REQUIRE_FALSE(val);
        }
    }

    SECTION("Non-equal iterators")
    {
        SECTION("Runtime")
        {
            It a{0, 1};
            It b{1, 2};
            REQUIRE(a != b);
        }

        SECTION("Compile-time")
        {
            static constexpr auto val = []() {
                It a{0, 1};
                It b{1, 2};
                return a != b;
            }();

            STATIC_REQUIRE(val);
        }
    }
}

TEMPLATE_TEST_CASE("[Range::Iterator] - operator*", "[zeus]", int, float)
{
    using It = typename Range<TestType>::Iterator;

    SECTION("Runtime")
    {
        It it{0, 2};
        REQUIRE(*it == 0);
    }

    SECTION("Compile-time")
    {
        static constexpr auto val = []() {
            It it{0, 2};
            return *it;
        }();

        STATIC_REQUIRE(val == 0);
    }
}

TEMPLATE_TEST_CASE("[Range] - begin", "[zeus]", int, float)
{
    SECTION("Runtime")
    {
        Range<TestType> r{10};
        REQUIRE(*r.begin() == 0);
    }

    SECTION("Compile-time")
    {
        static constexpr auto val = []() {
            Range<TestType> r{10};
            return *r.begin();
        }();

        STATIC_REQUIRE(val == 0);
    }
}

TEMPLATE_TEST_CASE("[Range] - end", "[zeus]", int, float)
{
    SECTION("Runtime")
    {
        Range<TestType> r{10};
        REQUIRE(*r.end() == 10);
    }

    SECTION("Compile-time")
    {
        static constexpr auto val = []() {
            Range<TestType> r{10};
            return *r.end();
        }();

        STATIC_REQUIRE(val == 10);
    }
}

TEMPLATE_TEST_CASE("[Range] - operator==", "[zeus]", int, float)
{
    SECTION("Equal ranges")
    {
        SECTION("Runtime")
        {
            Range<TestType> a1{0};
            Range<TestType> b1{2, 1, 3};
            REQUIRE(a1 == b1);

            Range<TestType> a2{0, 3, 2};
            Range<TestType> b2{0, 4, 2};
            REQUIRE(a2 == b2);
        }

        SECTION("Compile-time")
        {
            static constexpr auto val1 = []() {
                Range<TestType> a{0};
                Range<TestType> b{2, 1, 3};
                return a == b;
            }();

            static constexpr auto val2 = []() {
                Range<TestType> a{0, 3, 2};
                Range<TestType> b{0, 4, 2};
                return a == b;
            }();

            STATIC_REQUIRE(val1);
            STATIC_REQUIRE(val2);
        }
    }

    SECTION("Non-equal ranges")
    {
        SECTION("Runtime")
        {
            Range<TestType> a1{0};
            Range<TestType> b1{10};
            REQUIRE_FALSE(a1 == b1);

            Range<TestType> a2{0, 10, 2};
            Range<TestType> b2{0, 10, 3};
            REQUIRE_FALSE(a2 == b2);
        }

        SECTION("Compile-time")
        {
            static constexpr auto val1 = []() {
                Range<TestType> a{0};
                Range<TestType> b{10};
                return a == b;
            }();

            static constexpr auto val2 = []() {
                Range<TestType> a{0, 10, 2};
                Range<TestType> b{0, 10, 3};
                return a == b;
            }();

            STATIC_REQUIRE_FALSE(val1);
            STATIC_REQUIRE_FALSE(val2);
        }
    }
}

TEMPLATE_TEST_CASE("[Range] - operator!=", "[zeus]", int, float)
{
    SECTION("Equal ranges")
    {
        SECTION("Runtime")
        {
            Range<TestType> a1{0};
            Range<TestType> b1{2, 1, 3};
            REQUIRE_FALSE(a1 != b1);

            Range<TestType> a2{0, 3, 2};
            Range<TestType> b2{0, 4, 2};
            REQUIRE_FALSE(a2 != b2);
        }

        SECTION("Compile-time")
        {
            static constexpr auto val1 = []() {
                Range<TestType> a{0};
                Range<TestType> b{2, 1, 3};
                return a != b;
            }();

            static constexpr auto val2 = []() {
                Range<TestType> a{0, 3, 2};
                Range<TestType> b{0, 4, 2};
                return a != b;
            }();

            STATIC_REQUIRE_FALSE(val1);
            STATIC_REQUIRE_FALSE(val2);
        }
    }

    SECTION("Non-equal ranges")
    {
        SECTION("Runtime")
        {
            Range<TestType> a1{0};
            Range<TestType> b1{10};
            REQUIRE(a1 != b1);

            Range<TestType> a2{0, 10, 2};
            Range<TestType> b2{0, 10, 3};
            REQUIRE(a2 != b2);
        }

        SECTION("Compile-time")
        {
            static constexpr auto val1 = []() {
                Range<TestType> a{0};
                Range<TestType> b{10};
                return a != b;
            }();

            static constexpr auto val2 = []() {
                Range<TestType> a{0, 10, 2};
                Range<TestType> b{0, 10, 3};
                return a != b;
            }();

            STATIC_REQUIRE(val1);
            STATIC_REQUIRE(val2);
        }
    }
}

TEMPLATE_TEST_CASE("[range] - range", "[zeus]", int, float)
{
    SECTION("end")
    {
        SECTION("Runtime")
        {
            auto r = range(10);
            REQUIRE(r == Range<int>(10));
        }

        SECTION("Compile-time")
        {
            static constexpr auto r = []() {
                return range(10);
            }();

            STATIC_REQUIRE(r == Range<int>(10));
        }
    }

    SECTION("begin + end")
    {
        SECTION("Runtime")
        {
            auto r = range(0, 10);
            REQUIRE(r == Range<int>(0, 10));
        }

        SECTION("Compile-time")
        {
            static constexpr auto r = []() {
                return range(0, 10);
            }();

            STATIC_REQUIRE(r == Range<int>(0, 10));
        }
    }

    SECTION("begin + end + step")
    {
        SECTION("Runtime")
        {
            auto r = range(0, 10, 2);
            REQUIRE(r == Range<int>(0, 10, 2));
        }

        SECTION("Compile-time")
        {
            static constexpr auto r = []() {
                return range(0, 10, 2);
            }();

            STATIC_REQUIRE(r == Range<int>(0, 10, 2));
        }
    }
}

TEMPLATE_TEST_CASE("[Range] - usability", "[zeus]", int, float)
{
    const std::vector<int> expected{0, 1, 2, 3, 4};

    SECTION("Range-based loop")
    {
        std::vector<int> res;
        for (auto i : Range{5})
        {
            res.push_back(i);
        }

        REQUIRE(res == expected);
    }

    SECTION("Fill container")
    {
        Range r{5};
        std::vector<int> res(r.begin(), r.end());
        auto it = res.begin();
        REQUIRE(res == expected);
    }

    SECTION("Algorithm")
    {
        Range r{0, 10, 2};
        std::vector<int> res(5);
        std::transform(r.begin(), r.end(), res.begin(), [](auto a) {
            return a / 2;
        });
        REQUIRE(res == expected);
    }
}
