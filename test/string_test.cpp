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
    static constexpr char delim{'_'};

    SECTION("Base split function")
    {
        SECTION("Runtime")
        {
            SECTION("Empty string")
            {
                const std::string s;
                std::vector<std::string> expected;

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
                const std::string s = "some random text";
                std::vector<std::string> expected{s};

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
                const std::string s = "some random text";
                std::vector<std::string> expected(s.size() + 1);

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
                const std::string s = "some_random_text";
                std::vector<std::string> expected{"some", "random", "text"};

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
                const std::string s = "some_random_text";
                std::vector<std::string> expected{"some", "random_text"};

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
                    const std::string s;
                    const std::vector<std::string> expected;

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
                    const std::string s = "some random text";
                    const std::vector<std::string> expected{s};

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
                    const std::string s = "some random text";
                    const std::vector<std::string> expected(s.size() + 1);

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
                    const std::string s = "some_random_text";
                    const std::vector<std::string> expected{{"some"},
                                                            {"random"},
                                                            {"text"}};

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
                    const std::string s = "some_random_text";
                    const std::vector<std::string> expected{{"some"}, {"random_text"}};

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
            const std::string s = "some random text";
            std::vector<std::string> expected{"some", "random", "text"};

            auto items = zeus::split(s);
            REQUIRE(items == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const std::string s = "some random text";
                const std::vector<std::string> expected{{"some"}, {"random"}, {"text"}};

                auto items = zeus::split(s);
                return items == expected;
            }();

            STATIC_REQUIRE(res);
        }
    }

    SECTION("Split: str, int")
    {
        SECTION("Runtime")
        {
            const std::string s = "some random text";
            std::vector<std::string> expected{"some", "random text"};

            auto items = zeus::split(s, 1);
            REQUIRE(items == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const std::string s = "some random text";
                const std::vector<std::string> expected{{"some"}, {"random text"}};

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
            const std::string s = "some_random_text";
            std::vector<std::string> expected{"some", "random", "text"};

            auto items = zeus::split(s, delim);
            REQUIRE(items == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const std::string s = "some_random_text";
                const std::vector<std::string> expected{{"some"}, {"random"}, {"text"}};

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
            const std::string s = "some_random_text";
            std::vector<std::string> expected{"some", "random_text"};

            auto items = zeus::split(
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
                const std::string s = "some_random_text";
                const std::vector<std::string> expected{{"some"}, {"random_text"}};

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

TEST_CASE("[string] - rstrip", "[zeus]")
{
    SECTION("Base rstrip function")
    {
        SECTION("Runtime")
        {
            const std::string s  = "some random text,,,,";
            std::string expected = "some random text";

            auto res = zeus::rstrip(s, [](char c) {
                return c == ',';
            });

            REQUIRE(res == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const std::string s        = "some random text,,,,";
                const std::string expected = "some random text";

                auto res = zeus::rstrip(s, [](char c) {
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
            const std::string s  = "some random text    ";
            std::string expected = "some random text";

            auto res = zeus::rstrip(s);

            REQUIRE(res == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const std::string s        = "some random text    ";
                const std::string expected = "some random text";

                auto res = zeus::rstrip(s);

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
            const std::string s  = ",,,,some random text";
            std::string expected = "some random text";

            auto res = zeus::lstrip(s, [](char c) {
                return c == ',';
            });

            REQUIRE(res == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const std::string s        = ",,,,some random text";
                const std::string expected = "some random text";

                auto res = zeus::lstrip(s, [](char c) {
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
            const std::string s  = "    some random text";
            std::string expected = "some random text";

            auto res = zeus::lstrip(s);

            REQUIRE(res == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const std::string s        = "    some random text";
                const std::string expected = "some random text";

                auto res = zeus::lstrip(s);

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
            const std::string s  = ",,,,some random text,,,,";
            std::string expected = "some random text";

            auto res = zeus::strip(s, [](char c) {
                return c == ',';
            });

            REQUIRE(res == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const std::string s        = ",,,,some random text,,,,";
                const std::string expected = "some random text";

                auto res = zeus::strip(s, [](char c) {
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
            const std::string s  = "    some random text    ";
            std::string expected = "some random text";

            auto res = zeus::strip(s);

            REQUIRE(res == expected);
        }

        SECTION("Compile-time")
        {
            constexpr bool res = []() {
                const std::string s        = "    some random text    ";
                const std::string expected = "some random text";

                auto res = zeus::strip(s);

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
                const std::string s;
                std::vector<std::string> expected;

                auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("No newlines")
            {
                const std::string s = "some random text";
                std::vector<std::string> expected{"some random text"};

                auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("Newline")
            {
                const std::string s = "some\nrandom\ntext\n";
                std::vector<std::string> expected{"some", "random", "text"};

                auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("Carriage return")
            {
                const std::string s = "some\rrandom\rtext\r";
                std::vector<std::string> expected{"some", "random", "text"};

                auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("CRLF")
            {
                const std::string s = "some\r\nrandom\r\ntext\r\n";
                std::vector<std::string> expected{"some", "random", "text"};

                auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("Multiple newlines")
            {
                const std::string s = "some\n\n\n";
                std::vector<std::string> expected{"some", "", ""};

                auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("Multiple carriage returns")
            {
                const std::string s = "some\r\r\r";
                std::vector<std::string> expected{"some", "", ""};

                auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("Multiple CRLF")
            {
                const std::string s = "some\r\n\r\n\r\n";
                std::vector<std::string> expected{"some", "", ""};

                auto lines = zeus::split_lines(s, false);
                REQUIRE(lines == expected);
            }

            SECTION("Keep newline")
            {
                const std::string s = "some\nrandom\ntext\n";
                std::vector<std::string> expected{"some\n", "random\n", "text\n"};

                auto lines = zeus::split_lines(s, true);
                REQUIRE(lines == expected);
            }

            SECTION("Keep carriage return")
            {
                const std::string s = "some\rrandom\rtext\r";
                std::vector<std::string> expected{"some\r", "random\r", "text\r"};

                auto lines = zeus::split_lines(s, true);
                REQUIRE(lines == expected);
            }

            SECTION("Keep CRLF")
            {
                const std::string s = "some\r\nrandom\r\ntext\r\n";
                std::vector<std::string> expected{"some\r\n", "random\r\n", "text\r\n"};

                auto lines = zeus::split_lines(s, true);
                REQUIRE(lines == expected);
            }

            SECTION("Keep multiple newlines")
            {
                const std::string s = "some\n\n\n";
                std::vector<std::string> expected{"some\n", "\n", "\n"};

                auto lines = zeus::split_lines(s, true);
                REQUIRE(lines == expected);
            }

            SECTION("Keep multiple carriage returns")
            {
                const std::string s = "some\r\r\r";
                std::vector<std::string> expected{"some\r", "\r", "\r"};

                auto lines = zeus::split_lines(s, true);
                REQUIRE(lines == expected);
            }

            SECTION("Keep multiple CRLF")
            {
                const std::string s = "some\r\n\r\n\r\n";
                std::vector<std::string> expected{"some\r\n", "\r\n", "\r\n"};

                auto lines = zeus::split_lines(s, true);
                REQUIRE(lines == expected);
            }
        }

        SECTION("Compile-time")
        {
            SECTION("Empty string")
            {
                constexpr bool res = []() {
                    const std::string s;
                    const std::vector<std::string> expected;

                    auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("No newlines")
            {
                constexpr bool res = []() {
                    const std::string s = "some random text";
                    const std::vector<std::string> expected{{"some random text"}};

                    auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Newline")
            {
                constexpr bool res = []() {
                    const std::string s = "some\nrandom\ntext\n";
                    const std::vector<std::string> expected{{"some"},
                                                            {"random"},
                                                            {"text"}};

                    auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Carriage return")
            {
                constexpr bool res = []() {
                    const std::string s = "some\rrandom\rtext\r";
                    const std::vector<std::string> expected{{"some"},
                                                            {"random"},
                                                            {"text"}};

                    auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("CRLF")
            {
                constexpr bool res = []() {
                    const std::string s = "some\r\nrandom\r\ntext\r\n";
                    const std::vector<std::string> expected{{"some"},
                                                            {"random"},
                                                            {"text"}};

                    auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Multiple newlines")
            {
                constexpr bool res = []() {
                    const std::string s = "some\n\n\n";
                    const std::vector<std::string> expected{{"some"}, {""}, {""}};

                    auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Multiple carriage returns")
            {
                constexpr bool res = []() {
                    const std::string s = "some\r\r\r";
                    const std::vector<std::string> expected{{"some"}, {""}, {""}};

                    auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Multiple CRLF")
            {
                constexpr bool res = []() {
                    const std::string s = "some\r\n\r\n\r\n";
                    const std::vector<std::string> expected{{"some"}, {""}, {""}};

                    auto lines = zeus::split_lines(s, false);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Keep newline")
            {
                constexpr bool res = []() {
                    const std::string s = "some\nrandom\ntext\n";
                    const std::vector<std::string> expected{{"some\n"},
                                                            {"random\n"},
                                                            {"text\n"}};

                    auto lines = zeus::split_lines(s, true);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Keep carriage return")
            {
                constexpr bool res = []() {
                    const std::string s = "some\rrandom\rtext\r";
                    const std::vector<std::string> expected{{"some\r"},
                                                            {"random\r"},
                                                            {"text\r"}};

                    auto lines = zeus::split_lines(s, true);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Keep CRLF")
            {
                constexpr bool res = []() {
                    const std::string s = "some\r\nrandom\r\ntext\r\n";
                    const std::vector<std::string> expected{{"some\r\n"},
                                                            {"random\r\n"},
                                                            {"text\r\n"}};

                    auto lines = zeus::split_lines(s, true);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Keep multiple newlines")
            {
                constexpr bool res = []() {
                    const std::string s = "some\n\n\n";
                    const std::vector<std::string> expected{{"some\n"}, {"\n"}, {"\n"}};

                    auto lines = zeus::split_lines(s, true);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Keep multiple carriage returns")
            {
                constexpr bool res = []() {
                    const std::string s = "some\r\r\r";
                    const std::vector<std::string> expected{{"some\r"}, {"\r"}, {"\r"}};

                    auto lines = zeus::split_lines(s, true);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }

            SECTION("Keep multiple CRLF")
            {
                constexpr bool res = []() {
                    const std::string s = "some\r\n\r\n\r\n";
                    const std::vector<std::string> expected{{"some\r\n"},
                                                            {"\r\n"},
                                                            {"\r\n"}};

                    auto lines = zeus::split_lines(s, true);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }
        }

        SECTION("split_lines: str")
        {
            SECTION("Runtime")
            {
                const std::string s = "some\nrandom\ntext\n";
                std::vector<std::string> expected{"some", "random", "text"};

                auto lines = zeus::split_lines(s);
                REQUIRE(lines == expected);
            }

            SECTION("Compile-time")
            {
                constexpr bool res = []() {
                    const std::string s = "some\nrandom\ntext\n";
                    const std::vector<std::string> expected{{"some"},
                                                            {"random"},
                                                            {"text"}};

                    auto lines = zeus::split_lines(s);
                    return lines == expected;
                }();

                STATIC_REQUIRE(res);
            }
        }
    }
}
