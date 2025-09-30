#include <zeus/string.hpp>

#include <catch2/catch_test_macros.hpp>

#include <string>
#include <vector>

TEST_CASE("[string] - is_whitespace", "[zeus]")
{
    REQUIRE(zeus::is_whitespace(' '));
    REQUIRE(zeus::is_whitespace('\f'));
    REQUIRE(zeus::is_whitespace('\n'));
    REQUIRE(zeus::is_whitespace('\r'));
    REQUIRE(zeus::is_whitespace('\t'));
    REQUIRE(zeus::is_whitespace('\v'));

    REQUIRE_FALSE(zeus::is_whitespace('c'));
}

TEST_CASE("[string] DelimiterFunctor concept", "[zeus]")
{
    SECTION("Valid functor")
    {
        constexpr auto fun = [](char) {
            return false;
        };
        STATIC_REQUIRE(zeus::DelimiterFunctor<decltype(fun)>);
    }

    SECTION("Invalid functors")
    {
        constexpr auto void_fun = [](char) {};
        STATIC_REQUIRE_FALSE(zeus::DelimiterFunctor<decltype(void_fun)>);

        constexpr auto str_fun = [](std::string) {
            return false;
        };
        STATIC_REQUIRE_FALSE(zeus::DelimiterFunctor<decltype(str_fun)>);
    }
}

TEST_CASE("[string] - split", "[zeus]")
{
    static constexpr auto delim{'_'};

    SECTION("Base split function")
    {
        SECTION("Runtime")
        {
            SECTION("Empty string")
            {
                const auto s = std::string{};
                const auto expected = std::vector<std::string>{};

                auto items = zeus::split(
                    s,
                    [](char) {
                        return false;
                    },
                    -1);
                REQUIRE(items == expected);
            }

            SECTION("No delimiters")
            {
                const auto s = std::string{"some random text"};
                const auto expected = std::vector{s};

                auto items = zeus::split(
                    s,
                    [](char) {
                        return false;
                    },
                    -1);
                REQUIRE(items == expected);
            }

            SECTION("All chars are delimiters")
            {
                const auto s = std::string{"some random text"};
                const auto expected = std::vector<std::string>(s.size() + 1);

                auto items = zeus::split(
                    s,
                    [](char) {
                        return true;
                    },
                    -1);
                REQUIRE(items == expected);
            }

            SECTION("Specific delimiter")
            {
                const auto s = std::string{"some_random_text"};
                const auto expected = std::vector<std::string>{"some", "random", "text"};

                auto items = zeus::split(
                    s,
                    [](char c) {
                        return c == delim;
                    },
                    -1);
                REQUIRE(items == expected);
            }

            SECTION("Return max_split")
            {
                const auto s = std::string{"some_random_text"};
                const auto expected = std::vector<std::string>{"some", "random_text"};

                auto items = zeus::split(
                    s,
                    [](char c) {
                        return c == delim;
                    },
                    1);
                REQUIRE(items == expected);
            }
        }

        SECTION("Compile-time")
        {
            SECTION("Empty string")
            {
                constexpr bool res = []() {
                    const auto s = std::string{};
                    const auto expected = std::vector<std::string>{};

                    auto items = zeus::split(
                        s,
                        [](char) {
                            return false;
                        },
                        -1);
                    return items == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("No delimiters")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some random text"};
                    const auto expected = std::vector{s};

                    auto items = zeus::split(
                        s,
                        [](char) {
                            return false;
                        },
                        -1);
                    return items == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("All chars are delimiters")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some random text"};
                    const auto expected = std::vector<std::string>(s.size() + 1);

                    auto items = zeus::split(
                        s,
                        [](char) {
                            return true;
                        },
                        -1);
                    return items == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Specific delimiter")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some_random_text"};
                    const auto expected =
                        std::vector<std::string>{"some", "random", "text"};

                    auto items = zeus::split(
                        s,
                        [](char c) {
                            return c == delim;
                        },
                        -1);
                    return items == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Return max_split")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some_random_text"};
                    const auto expected = std::vector<std::string>{"some", "random_text"};

                    auto items = zeus::split(
                        s,
                        [](char c) {
                            return c == delim;
                        },
                        1);
                    return items == expected;
                }();

                STATIC_REQUIRE(res);
            }
        }
    }

    SECTION("Split: str")
    {
        SECTION("Runtime")
        {
            const auto s = std::string{"some random text"};
            const auto expected = std::vector<std::string>{"some", "random", "text"};

            const auto items = zeus::split(s);
            REQUIRE(items == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const auto s = std::string{"some random text"};
                const auto expected = std::vector<std::string>{"some", "random", "text"};

                const auto items = zeus::split(s);
                return items == expected;
            }();

            STATIC_REQUIRE(res);
        }
    }

    SECTION("Split: str, int")
    {
        SECTION("Runtime")
        {
            const auto s = std::string{"some random text"};
            const auto expected = std::vector<std::string>{"some", "random text"};

            const auto items = zeus::split(s, 1);
            REQUIRE(items == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const auto s = std::string{"some random text"};
                const auto expected = std::vector<std::string>{"some", "random text"};

                auto items = zeus::split(s, 1);
                return items == expected;
            }();

            STATIC_REQUIRE(res);
        }
    }

    SECTION("Split: str, char")
    {
        SECTION("Runtime")
        {
            const auto s = std::string{"some_random_text"};
            const auto expected = std::vector<std::string>{"some", "random", "text"};

            const auto items = zeus::split(s, delim);
            REQUIRE(items == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const auto s = std::string{"some_random_text"};
                const auto expected = std::vector<std::string>{"some", "random", "text"};

                auto items = zeus::split(
                    s,
                    [](char c) {
                        return c == delim;
                    },
                    -1);
                return items == expected;
            }();
            STATIC_REQUIRE(res);
        }
    }

    SECTION("Split: str, char, int")
    {
        SECTION("Runtime")
        {
            const auto s = std::string{"some_random_text"};
            const auto expected = std::vector<std::string>{"some", "random_text"};

            const auto items = zeus::split(
                s,
                [](char c) {
                    return c == delim;
                },
                1);

            REQUIRE(items == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const auto s = std::string{"some_random_text"};
                const auto expected = std::vector<std::string>{"some", "random_text"};

                const auto items = zeus::split(
                    s,
                    [](char c) {
                        return c == delim;
                    },
                    1);

                return items == expected;
            }();

            STATIC_REQUIRE(res);
        }
    }
}

TEST_CASE("[string] - rstrip", "[zeus]")
{
    SECTION("Base rstrip function")
    {
        SECTION("Runtime")
        {
            const auto s = std::string{"some random text,,,,"};
            const auto expected = std::string{"some random text"};

            const auto res = zeus::rstrip(s, [](char c) {
                return c == ',';
            });

            REQUIRE(res == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const auto s = std::string{"some random text,,,,"};
                const auto expected = std::string{"some random text"};

                const auto res = zeus::rstrip(s, [](char c) {
                    return c == ',';
                });

                return res == expected;
            }();

            STATIC_REQUIRE(res);
        }
    }

    SECTION("rstrip: str")
    {
        SECTION("Runtime")
        {
            const auto s = std::string{"some random text    "};
            const auto expected = std::string{"some random text"};

            const auto res = zeus::rstrip(s);

            REQUIRE(res == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const auto s = std::string{"some random text    "};
                const auto expected = std::string{"some random text"};

                const auto res = zeus::rstrip(s);

                return res == expected;
            }();

            STATIC_REQUIRE(res);
        }
    }
}

TEST_CASE("[string] - lstrip", "[zeus]")
{
    SECTION("Base lstrip function")
    {
        SECTION("Runtime")
        {
            const auto s = std::string{",,,,some random text"};
            const auto expected = std::string{"some random text"};

            const auto res = zeus::lstrip(s, [](char c) {
                return c == ',';
            });

            REQUIRE(res == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const auto s = std::string{",,,,some random text"};
                const auto expected = std::string{"some random text"};

                const auto res = zeus::lstrip(s, [](char c) {
                    return c == ',';
                });

                return res == expected;
            }();

            STATIC_REQUIRE(res);
        }
    }

    SECTION("lstrip: str")
    {
        SECTION("Runtime")
        {
            const auto s = std::string{"    some random text"};
            const auto expected = std::string{"some random text"};

            const auto res = zeus::lstrip(s);

            REQUIRE(res == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const auto s = std::string{"    some random text"};
                const auto expected = std::string{"some random text"};

                const auto res = zeus::lstrip(s);

                return res == expected;
            }();

            STATIC_REQUIRE(res);
        }
    }
}

TEST_CASE("[string] - strip", "[zeus]")
{
    SECTION("Base strip function")
    {
        SECTION("Runtime")
        {
            const auto s = std::string{",,,,some random text,,,,"};
            const auto expected = std::string{"some random text"};

            const auto res = zeus::strip(s, [](char c) {
                return c == ',';
            });

            REQUIRE(res == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const auto s = std::string{",,,,some random text,,,,"};
                const auto expected = std::string{"some random text"};

                const auto res = zeus::strip(s, [](char c) {
                    return c == ',';
                });

                return res == expected;
            }();

            STATIC_REQUIRE(res);
        }
    }

    SECTION("strip: str")
    {
        SECTION("Runtime")
        {
            const auto s = std::string{"    some random text    "};
            const auto expected = std::string{"some random text"};

            const auto res = zeus::strip(s);

            REQUIRE(res == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const auto s = std::string{"    some random text    "};
                const auto expected = std::string{"some random text"};

                const auto res = zeus::strip(s);

                return res == expected;
            }();

            STATIC_REQUIRE(res);
        }
    }
}

TEST_CASE("[string] - split_lines", "[zeus]")
{
    SECTION("Base split_lines function")
    {
        SECTION("Runtime")
        {
            SECTION("Empty string")
            {
                const auto s = std::string{};
                const auto expected = std::vector<std::string>{};

                const auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("No newlines")
            {
                const auto s = std::string{"some random text"};
                const auto expected = std::vector<std::string>{"some random text"};

                const auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("Newline")
            {
                const auto s = std::string{"some\nrandom\ntext\n"};
                const auto expected = std::vector<std::string>{"some", "random", "text"};

                const auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("Carriage return")
            {
                const auto s = std::string{"some\rrandom\rtext\r"};
                const auto expected = std::vector<std::string>{"some", "random", "text"};

                const auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("CRLF")
            {
                const auto s = std::string{"some\r\nrandom\r\ntext\r\n"};
                const auto expected = std::vector<std::string>{"some", "random", "text"};

                const auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("Multiple newlines")
            {
                const auto s = std::string{"some\n\n\n"};
                const auto expected = std::vector<std::string>{"some", "", ""};

                const auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("Multiple carriage returns")
            {
                const auto s = std::string{"some\r\r\r"};
                const auto expected = std::vector<std::string>{"some", "", ""};

                const auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("Multiple CRLF")
            {
                const auto s = std::string{"some\r\n\r\n\r\n"};
                const auto expected = std::vector<std::string>{"some", "", ""};

                const auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("Keep newline")
            {
                const auto s = std::string{"some\nrandom\ntext\n"};
                const auto expected =
                    std::vector<std::string>{"some\n", "random\n", "text\n"};

                const auto lines = zeus::split_lines(s, true);
                REQUIRE(lines == expected);
            }

            SECTION("Keep carriage return")
            {
                const auto s = std::string{"some\rrandom\rtext\r"};
                const auto expected =
                    std::vector<std::string>{"some\r", "random\r", "text\r"};

                const auto lines = zeus::split_lines(s, true);
                REQUIRE(lines == expected);
            }

            SECTION("Keep CRLF")
            {
                const auto s = std::string{"some\r\nrandom\r\ntext\r\n"};
                const auto expected =
                    std::vector<std::string>{"some\r\n", "random\r\n", "text\r\n"};

                const auto lines = zeus::split_lines(s, true);
                REQUIRE(lines == expected);
            }

            SECTION("Keep multiple newlines")
            {
                const auto s = std::string{"some\n\n\n"};
                const auto expected = std::vector<std::string>{"some\n", "\n", "\n"};

                const auto lines = zeus::split_lines(s, true);
                REQUIRE(lines == expected);
            }

            SECTION("Keep multiple carriage returns")
            {
                const auto s = std::string{"some\r\r\r"};
                const auto expected = std::vector<std::string>{"some\r", "\r", "\r"};

                const auto lines = zeus::split_lines(s, true);
                REQUIRE(lines == expected);
            }

            SECTION("Keep multiple CRLF")
            {
                const auto s = std::string{"some\r\n\r\n\r\n"};
                const auto expected =
                    std::vector<std::string>{"some\r\n", "\r\n", "\r\n"};

                const auto lines = zeus::split_lines(s, true);
                REQUIRE(lines == expected);
            }
        }

        SECTION("Compile-time")
        {
            SECTION("Empty string")
            {
                constexpr bool res = []() {
                    const auto s = std::string{};
                    const auto expected = std::vector<std::string>{};

                    const auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("No newlines")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some random text"};
                    const auto expected = std::vector<std::string>{"some random text"};

                    const auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Newline")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some\nrandom\ntext\n"};
                    const auto expected =
                        std::vector<std::string>{"some", "random", "text"};

                    const auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Carriage return")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some\rrandom\rtext\r"};
                    const auto expected =
                        std::vector<std::string>{"some", "random", "text"};

                    const auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("CRLF")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some\r\nrandom\r\ntext\r\n"};
                    const auto expected =
                        std::vector<std::string>{"some", "random", "text"};

                    const auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Multiple newlines")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some\n\n\n"};
                    const auto expected = std::vector<std::string>{"some", "", ""};

                    const auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Multiple carriage returns")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some\r\r\r"};
                    const auto expected = std::vector<std::string>{"some", "", ""};

                    const auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Multiple CRLF")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some\r\n\r\n\r\n"};
                    const auto expected = std::vector<std::string>{"some", "", ""};

                    const auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Keep newline")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some\nrandom\ntext\n"};
                    const auto expected =
                        std::vector<std::string>{"some\n", "random\n", "text\n"};

                    const auto lines = zeus::split_lines(s, true);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Keep carriage return")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some\rrandom\rtext\r"};
                    const auto expected =
                        std::vector<std::string>{"some\r", "random\r", "text\r"};

                    const auto lines = zeus::split_lines(s, true);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Keep CRLF")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some\r\nrandom\r\ntext\r\n"};
                    const auto expected =
                        std::vector<std::string>{"some\r\n", "random\r\n", "text\r\n"};

                    const auto lines = zeus::split_lines(s, true);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Keep multiple newlines")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some\n\n\n"};
                    const auto expected = std::vector<std::string>{"some\n", "\n", "\n"};

                    const auto lines = zeus::split_lines(s, true);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Keep multiple carriage returns")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some\r\r\r"};
                    const auto expected = std::vector<std::string>{"some\r", "\r", "\r"};

                    const auto lines = zeus::split_lines(s, true);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Keep multiple CRLF")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some\r\n\r\n\r\n"};
                    const auto expected =
                        std::vector<std::string>{"some\r\n", "\r\n", "\r\n"};

                    const auto lines = zeus::split_lines(s, true);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }
        }

        SECTION("split_lines: str")
        {
            SECTION("Runtime")
            {
                const auto s = std::string{"some\nrandom\ntext\n"};
                const auto expected = std::vector<std::string>{"some", "random", "text"};

                const auto lines = zeus::split_lines(s);
                REQUIRE(lines == expected);
            }

            SECTION("Compile-time")
            {
                constexpr bool res = []() {
                    const auto s = std::string{"some\nrandom\ntext\n"};
                    const auto expected =
                        std::vector<std::string>{"some", "random", "text"};

                    const auto lines = zeus::split_lines(s);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }
        }
    }
}
