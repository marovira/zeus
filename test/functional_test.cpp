#include <zeus/functional.hpp>

#include <catch2/catch.hpp>
#include <numeric>
#include <vector>

template<typename T>
inline bool vector_equal(std::vector<T> const& v1, std::vector<T> const& v2)
{
    if (v1.size() != v2.size())
    {
        return false;
    }

    for (std::size_t i{0}; i < v1.size(); ++i)
    {
        if (v1[i] != v2[i])
        {
            return false;
        }
    }

    return true;
}

TEMPLATE_TEST_CASE("[functional] - iota", "[zeus]", int, double)
{
    using zeus::iota;
    std::vector<TestType> result(10);
    std::iota(result.begin(), result.end(), TestType{1});
    std::vector<TestType> v(10);
    iota(v.begin(), v.end(), 1, 1);

    REQUIRE(vector_equal<TestType>(v, result));
}
