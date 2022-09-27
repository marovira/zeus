#include <zeus/config_parser.hpp>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

using zeus::ConfigParser;

TEST_CASE("[ConfigParser::Section] - insert", "[zeus]")
{
    ConfigParser::Section s;

    SECTION("Empty section")
    {
        REQUIRE(s.keys().size() == 0);
    }

    SECTION("Insert 1 key")
    {
        s.insert("foo", "1");
        REQUIRE(s.keys().size() == 1);
    }

    SECTION("Insert multiple keys")
    {
        s.insert("foo", "1");
        s.insert("bar", "2");
        s.insert("baz", "3");

        REQUIRE(s.keys().size() == 3);
    }
}

TEST_CASE("[ConfigParser::Section] - keys", "[zeus]")
{
    ConfigParser::Section s;

    SECTION("Empty section")
    {
        REQUIRE(s.keys().size() == 0);
    }

    SECTION("Single key")
    {
        std::string key{"foo"};
        s.insert(key, "1");

        auto keys = s.keys();
        REQUIRE(keys.size() == 1);
        REQUIRE(keys[0] == key);
    }

    SECTION("Multiple keys")
    {
        std::vector<std::string> expected_keys{"foo", "bar", "baz"};
        std::sort(expected_keys.begin(), expected_keys.end());

        for (int i{0}; auto key : expected_keys)
        {
            s.insert(key, std::to_string(i));
            ++i;
        }

        auto keys = s.keys();
        REQUIRE(keys.size() == expected_keys.size());
        REQUIRE(keys == expected_keys);
    }
}

TEST_CASE("[ConfigParser::Section] - exists", "[zeus]")
{
    ConfigParser::Section s;

    SECTION("Empty section")
    {
        REQUIRE_FALSE(s.exists("foo"));
    }

    SECTION("Non-empty section")
    {
        s.insert("foo", "1");

        SECTION("valid value")
        {
            REQUIRE(s.exists("foo"));
        }

        SECTION("invalid value")
        {
            REQUIRE_FALSE(s.exists("bar"));
        }
    }
}

TEST_CASE("[ConfigParser::Section] - operator[]", "[zeus]")
{
    SECTION("const version")
    {
        SECTION("Empty section")
        {
            const ConfigParser::Section s;
            REQUIRE_THROWS(s["foo"]);
        }

        SECTION("Non-empty section")
        {
            ConfigParser::Section sec;
            sec.insert("foo", "1");
            sec.insert("bar", "2");
            sec.insert("baz", "3");

            const auto s = sec;

            SECTION("Valid key")
            {
                REQUIRE(s["foo"] == "1");
                REQUIRE(s["bar"] == "2");
                REQUIRE(s["baz"] == "3");
            }

            SECTION("Invalid key")
            {
                REQUIRE_THROWS(s["bumble"]);
            }
        }
    }

    SECTION("Non-const version")
    {
        SECTION("Empty section")
        {
            ConfigParser::Section s;
            REQUIRE_THROWS(s["foo"]);
        }

        SECTION("Non-empty section")
        {
            ConfigParser::Section s;
            s.insert("foo", "1");
            s.insert("bar", "2");
            s.insert("baz", "3");

            SECTION("Valid key")
            {
                REQUIRE(s["foo"] == "1");
                REQUIRE(s["bar"] == "2");
                REQUIRE(s["baz"] == "3");
            }

            SECTION("Invalid key")
            {
                REQUIRE_THROWS(s["bumble"]);
            }
        }
    }
}

TEST_CASE("[CofingParser::Section] - value_as", "[zeus]")
{
    ConfigParser::Section s;

    SECTION("int")
    {
        s.insert("int", "1");
        REQUIRE(s.value_as<int>("int") == 1);
    }

    SECTION("float")
    {
        s.insert("float", "0.1");
        REQUIRE(s.value_as<float>("float") == 0.1f);
    }

    SECTION("bool")
    {
        SECTION("yes/no")
        {
            s.insert("yes", "yes");
            s.insert("no", "no");

            REQUIRE(s.value_as<bool>("yes"));
            REQUIRE_FALSE(s.value_as<bool>("no"));
        }

        SECTION("on/off")
        {
            s.insert("on", "on");
            s.insert("off", "off");

            REQUIRE(s.value_as<bool>("on"));
            REQUIRE_FALSE(s.value_as<bool>("off"));
        }

        SECTION("true/false")
        {
            s.insert("true", "true");
            s.insert("false", "false");

            REQUIRE(s.value_as<bool>("true"));
            REQUIRE_FALSE(s.value_as<bool>("false"));
        }

        SECTION("1/0")
        {
            s.insert("1", "1");
            s.insert("0", "0");

            REQUIRE(s.value_as<bool>("1"));
            REQUIRE_FALSE(s.value_as<bool>("0"));
        }
    }
}

TEST_CASE("[ConfigParser] - insert", "[zeus]")
{
    ConfigParser c;

    SECTION("Empty parser")
    {
        REQUIRE(c.sections().size() == 0);
    }

    SECTION("Single section")
    {
        ConfigParser::Section s;
        c.insert("foo", s);
        REQUIRE(c.sections().size() == 1);
    }

    SECTION("Multiple sections")
    {
        ConfigParser::Section s;
        c.insert("foo", s);
        c.insert("bar", s);
        c.insert("baz", s);
        REQUIRE(c.sections().size() == 3);
    }
}

namespace zeus
{
    bool operator==(ConfigParser::Section const& rhs, ConfigParser::Section const& lhs)
    {
        auto rhs_keys = rhs.keys();
        auto lhs_keys = lhs.keys();

        if (rhs_keys != lhs_keys)
        {
            return false;
        }

        for (std::size_t i{0}; i < rhs_keys.size(); ++i)
        {
            if (rhs[rhs_keys[i]] != lhs[lhs_keys[i]])
            {
                return false;
            }
        }

        return true;
    }
} // namespace zeus

TEST_CASE("[ConfigParser] - sections", "[zeus]")
{
    ConfigParser c;

    SECTION("Empty parser")
    {
        REQUIRE(c.sections().empty());
    }

    SECTION("Single section")
    {
        ConfigParser::Section s;
        c.insert("foo", s);

        auto sections = c.sections();
        REQUIRE(sections.size() == 1);
        REQUIRE(sections[0] == "foo");
    }

    SECTION("Multiple sections")
    {
        std::vector<std::string> names{"foo", "bar", "baz"};
        std::sort(names.begin(), names.end());

        ConfigParser::Section s;
        for (auto name : names)
        {
            c.insert(name, s);
        }

        auto sections = c.sections();
        REQUIRE(sections.size() == names.size());
        REQUIRE(sections == names);
    }
}

TEST_CASE("[ConfigParser] - exists", "[zeus]")
{
    ConfigParser c;

    SECTION("Empty parser")
    {
        REQUIRE_FALSE(c.exists("foo"));
    }

    SECTION("Non-empty parser")
    {
        ConfigParser::Section s;
        c.insert("foo", s);

        SECTION("Valid section")
        {
            REQUIRE(c.exists("foo"));
        }

        SECTION("Invalid section")
        {
            REQUIRE_FALSE(c.exists("bar"));
        }
    }
}

TEST_CASE("[ConfigParser] - operator[]", "[zeus]")
{
    SECTION("Const version")
    {
        SECTION("Empty parser")
        {
            const ConfigParser c;
            REQUIRE_THROWS(c["foo"]);
        }

        SECTION("Non_empty parser")
        {
            ConfigParser cfg;
            ConfigParser::Section s;
            cfg.insert("foo", s);
            cfg.insert("bar", s);
            cfg.insert("baz", s);

            const auto c = cfg;

            SECTION("Valid section")
            {
                REQUIRE(c["foo"] == s);
                REQUIRE(c["bar"] == s);
                REQUIRE(c["baz"] == s);
            }

            SECTION("Invalid section")
            {
                REQUIRE_THROWS(c["mumble"]);
            }
        }
    }

    SECTION("Non-const version")
    {
        SECTION("Empty parser")
        {
            ConfigParser c;
            REQUIRE_THROWS(c["foo"]);
        }

        SECTION("Non_empty parser")
        {
            ConfigParser c;
            ConfigParser::Section s;
            c.insert("foo", s);
            c.insert("bar", s);
            c.insert("baz", s);

            SECTION("Valid section")
            {
                REQUIRE(c["foo"] == s);
                REQUIRE(c["bar"] == s);
                REQUIRE(c["baz"] == s);
            }

            SECTION("Invalid section")
            {
                REQUIRE_THROWS(c["mumble"]);
            }
        }
    }
}

struct TestFile
{
    TestFile(std::string const& name, std::string const& contents) :
        name{name}
    {
        std::ofstream stream{name};
        stream << contents;
        stream.close();
    }

    ~TestFile()
    {
        namespace fs = std::filesystem;
        fs::remove(fs::path(name));
    }

    std::string name;
};

TEST_CASE("[ConfigParser] - read", "[zeus]")
{
    ConfigParser cfg;

    SECTION("Invalid file")
    {
        REQUIRE_FALSE(cfg.read("foo.ini"));
    }

    SECTION("Empty file")
    {
        TestFile f{"foo.ini", ""};
        REQUIRE(cfg.read(f.name));
        REQUIRE(cfg.sections().empty());
    }

    SECTION("File with comments")
    {
        TestFile f{"foo.ini",
                   "# A comment\n   # Another comment\n\n\t; Yet another comment\t\t"};
        REQUIRE(cfg.read(f.name));
        REQUIRE(cfg.sections().empty());
    }

    SECTION("File with sections")
    {
        TestFile f{"foo.ini",
                   "[Section 1]\n    [Section 2]    \n\n\t[Section 3]\t\t\n[    Section  "
                   "  4    "
                   "]\n[\tSection\t5\t]\n"};
        std::vector<std::string> expected_sections{"Section 1",
                                                   "Section 2",
                                                   "Section 3",
                                                   "    Section    4    ",
                                                   "\tSection\t5\t"};
        std::sort(expected_sections.begin(), expected_sections.end());

        REQUIRE(cfg.read(f.name));

        auto sections = cfg.sections();
        REQUIRE(sections.size() == 5);
        REQUIRE(sections == expected_sections);
    }

    SECTION("File with sections and keys")
    {
        TestFile f{"foo.ini",
                   "[Section 1]\nvar = 1\n    var_2 : foo\nvar_3 = 3    \n[Section 2]\n "
                   "var_4: 4\n Var_5 = 5"};

        std::vector<std::string> expected_sections{"Section 1", "Section 2"};
        ConfigParser::Section s1;
        s1.insert("var", "1");
        s1.insert("var_2", "foo");
        s1.insert("var_3", "3");

        ConfigParser::Section s2;
        s2.insert("var_4", "4");
        s2.insert("var_5", "5");

        REQUIRE(cfg.read(f.name));

        auto sections = cfg.sections();
        REQUIRE(sections.size() == 2);
        REQUIRE(sections == expected_sections);
        REQUIRE(cfg[sections[0]] == s1);
        REQUIRE(cfg[sections[1]] == s2);
    }
}
