#include <zeus/string.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("[string] - split", "[zeus]")
{
    const char delim = '.';

    SECTION("No delimiters")
    {
        std::string s                     = "some random text";
        std::vector<std::string> expected = {s};

        auto items = zeus::split(s, delim);
        REQUIRE(items == expected);
    }

    SECTION("Single delimiter at beginning")
    {
        std::string s                     = ".some random text";
        std::vector<std::string> expected = {"", "some random text"};

        auto items = zeus::split(s, delim);
        REQUIRE(items == expected);
    }

    SECTION("Single delimiter at end")
    {
        std::string s                     = "some random text.";
        std::vector<std::string> expected = {"some random text", ""};

        auto items = zeus::split(s, delim);
        REQUIRE(items == expected);
    }

    SECTION("Single delimiter in string")
    {
        std::string s = "some.random text";

        std::vector<std::string> expected = {"some", "random text"};

        auto items = zeus::split(s, delim);
        REQUIRE(items == expected);
    }

    SECTION("Multiple delimiters")
    {
        std::string s                     = ".some.random.text.";
        std::vector<std::string> expected = {"", "some", "random", "text", ""};

        auto items = zeus::split(s, delim);
        REQUIRE(items == expected);
    }
}

TEST_CASE("[string] - trim", "[zeus]")
{
    const std::string exp{"some text"};
    const std::string whitespace{" \f\n\r\t\v"};

    SECTION("Non-const input")
    {
        SECTION("No whitespace")
        {
            std::string s{"some text"};
            zeus::trim(s);
            REQUIRE(s == exp);
        }

        SECTION("Leading whitespace")
        {
            std::string s = whitespace + exp;

            zeus::trim(s);
            REQUIRE(s == exp);
        }

        SECTION("Trailing whitespace")
        {
            std::string s = exp + whitespace;

            zeus::trim(s);
            REQUIRE(s == exp);
        }

        SECTION("Leading and trailing whitespace")
        {
            std::string s = whitespace + exp + whitespace;

            zeus::trim(s);
            REQUIRE(s == exp);
        }
    }

    SECTION("Const input")
    {
        SECTION("No whitespace")
        {
            const std::string s{"some text"};
            REQUIRE(zeus::trim(s) == exp);
        }

        SECTION("Leading whitespace")
        {
            const std::string s = whitespace + exp;
            REQUIRE(zeus::trim(s) == exp);
        }

        SECTION("Trailing whitespace")
        {
            const std::string s = exp + whitespace;
            REQUIRE(zeus::trim(s) == exp);
        }

        SECTION("Leading and trailing whitespace")
        {
            const std::string s = whitespace + exp + whitespace;
            REQUIRE(zeus::trim(s) == exp);
        }
    }
}
