#include <zeus/enum_bitfield.hpp>

#include <catch2/catch_test_macros.hpp>

enum class Bits : unsigned char
{
    none = 0x0,
    a    = 0x01,
    b    = 0x02,
    c    = 0x04
};

using zeus::EnumBitfield;

TEST_CASE("[EnumBitfield] - constructors", "[zeus]")
{

    SECTION("Default constructor")
    {
        EnumBitfield<Bits> field;
        REQUIRE(field.get() == 0);
    }

    SECTION("Enum constructor")
    {
        EnumBitfield<Bits> field{Bits::a};
        REQUIRE(field.get() == 1);
    }

    SECTION("Constexpr default constructor")
    {
        static constexpr auto val = []() {
            EnumBitfield<Bits> field;
            return field.get();
        }();

        REQUIRE(val == 0);
    }

    SECTION("Constexpr enum constructor")
    {
        static constexpr auto val = []() {
            EnumBitfield<Bits> field{Bits::a};
            return field.get();
        }();

        REQUIRE(val == 1);
    }
}

TEST_CASE("[EnumBitfield] - operator&=", "[zeus]")
{
    SECTION("Non-constexpr")
    {
        EnumBitfield<Bits> field{Bits::a};

        SECTION("&= Bitfield")
        {
            field &= EnumBitfield<Bits>{Bits::a};
            REQUIRE(field.get() == 1);

            field &= EnumBitfield<Bits>{Bits::b};
            REQUIRE(field.get() == 0);
        }

        SECTION("&= enum")
        {
            field &= Bits::a;
            REQUIRE(field.get() == 1);

            field &= Bits::b;
            REQUIRE(field.get() == 0);
        }
    }

    SECTION("Contexpr")
    {
        SECTION("&= Bitfield")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field &= EnumBitfield<Bits>{Bits::a};
                    return field.get();
                }();

                REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field &= EnumBitfield<Bits>{Bits::b};
                    return field.get();
                }();

                REQUIRE(val == 0);
            }
        }

        SECTION("&= enum")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field &= Bits::a;
                    return field.get();
                }();

                REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field &= Bits::b;
                    return field.get();
                }();

                REQUIRE(val == 0);
            }
        }
    }
}

TEST_CASE("[EnumBitfield] - operator|=", "[zeus]")
{
    SECTION("Non-constexpr")
    {
        EnumBitfield<Bits> field{Bits::a};

        SECTION("|= Bitfield")
        {
            field |= EnumBitfield<Bits>{Bits::a};
            REQUIRE(field.get() == 1);

            field |= EnumBitfield<Bits>{Bits::b};
            REQUIRE(field.get() == 3);
        }

        SECTION("|= enum")
        {
            field |= Bits::a;
            REQUIRE(field.get() == 1);

            field |= Bits::b;
            REQUIRE(field.get() == 3);
        }
    }

    SECTION("Contexpr")
    {
        SECTION("|= Bitfield")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field |= EnumBitfield<Bits>{Bits::a};
                    return field.get();
                }();

                REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field |= EnumBitfield<Bits>{Bits::b};
                    return field.get();
                }();

                REQUIRE(val == 3);
            }
        }

        SECTION("|= enum")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field |= Bits::a;
                    return field.get();
                }();

                REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field |= Bits::b;
                    return field.get();
                }();

                REQUIRE(val == 3);
            }
        }
    }
}

TEST_CASE("[EnumBitfield] - opeartor&", "[zeus]")
{
    SECTION("Non-constexpr")
    {
        EnumBitfield<Bits> field{Bits::a};

        SECTION("& Bitfield")
        {
            auto val = field & EnumBitfield<Bits>{Bits::a};
            REQUIRE(val.get() == 1);

            val = field & EnumBitfield<Bits>{Bits::b};
            REQUIRE(val.get() == 0);
        }

        SECTION("& enum")
        {
            auto val = field & Bits::a;
            REQUIRE(val.get() == 1);

            val = field & Bits::b;
            REQUIRE(val.get() == 0);
        }
    }

    SECTION("Contexpr")
    {
        SECTION("& Bitfield")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field & EnumBitfield<Bits>{Bits::a}).get();
                }();

                REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field & EnumBitfield<Bits>{Bits::b}).get();
                }();

                REQUIRE(val == 0);
            }
        }

        SECTION("& enum")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field & Bits::a).get();
                }();

                REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field & Bits::b).get();
                }();

                REQUIRE(val == 0);
            }
        }
    }
}

TEST_CASE("[EnumBitfield] - operator|", "[zeus]")
{
    SECTION("Non-constexpr")
    {
        EnumBitfield<Bits> field{Bits::a};

        SECTION("| Bitfield")
        {
            auto val = field | EnumBitfield<Bits>{Bits::a};
            REQUIRE(val.get() == 1);

            val = field | EnumBitfield<Bits>{Bits::b};
            REQUIRE(val.get() == 3);
        }

        SECTION("| enum")
        {
            auto val = field | Bits::a;
            REQUIRE(val.get() == 1);

            val = field | Bits::b;
            REQUIRE(val.get() == 3);
        }
    }

    SECTION("Contexpr")
    {
        SECTION("| Bitfield")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field | EnumBitfield<Bits>{Bits::a}).get();
                }();

                REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field | EnumBitfield<Bits>{Bits::b}).get();
                }();

                REQUIRE(val == 3);
            }
        }

        SECTION("| enum")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field | Bits::a).get();
                }();

                REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field | Bits::b).get();
                }();

                REQUIRE(val == 3);
            }
        }
    }
}

TEST_CASE("[EnumBitfield] - operator bool", "[zeus]")
{
    SECTION("Non-constexpr")
    {
        REQUIRE(EnumBitfield<Bits>{Bits::a});
        REQUIRE_FALSE(EnumBitfield<Bits>{Bits::none});
    }

    SECTION("Constexpr")
    {
        static constexpr auto true_val = []() -> bool {
            return EnumBitfield<Bits>{Bits::a};
        }();

        static constexpr auto false_val = []() -> bool {
            return EnumBitfield<Bits>{Bits::none};
        }();

        REQUIRE(true_val);
        REQUIRE_FALSE(false_val);
    }
}

TEST_CASE("[EnumBitfield] - operator==", "[zeus]")
{
    SECTION("Non-constexpr")
    {
        EnumBitfield<Bits> val{Bits::a};

        SECTION("== Bitfield")
        {
            REQUIRE(val == EnumBitfield<Bits>{Bits::a});
            REQUIRE_FALSE(val == EnumBitfield<Bits>{Bits::b});
        }

        SECTION("== enum")
        {
            REQUIRE(val == Bits::a);
            REQUIRE_FALSE(val == Bits::b);
        }
    }

    SECTION("Constexpr")
    {
        SECTION("== Bitfield")
        {
            static constexpr auto true_val = []() {
                return EnumBitfield<Bits>{Bits::a} == EnumBitfield<Bits>{Bits::a};
            }();

            static constexpr auto false_val = []() {
                return EnumBitfield<Bits>{Bits::a} == EnumBitfield<Bits>{Bits::b};
            }();

            REQUIRE(true_val);
            REQUIRE_FALSE(false_val);
        }

        SECTION("== enum")
        {
            static constexpr auto true_val = []() {
                return EnumBitfield<Bits>{Bits::a} == Bits::a;
            }();

            static constexpr auto false_val = []() {
                return EnumBitfield<Bits>{Bits::a} == Bits::b;
            }();

            REQUIRE(true_val);
            REQUIRE_FALSE(false_val);
        }
    }
}

TEST_CASE("[EnumBitfield] - opeartor!=", "[zeus]")
{
    SECTION("Non-constexpr")
    {
        EnumBitfield<Bits> val{Bits::a};

        SECTION("!= Bitfield")
        {
            REQUIRE_FALSE(val != EnumBitfield<Bits>{Bits::a});
            REQUIRE(val != EnumBitfield<Bits>{Bits::b});
        }

        SECTION("!= enum")
        {
            REQUIRE_FALSE(val != Bits::a);
            REQUIRE(val != Bits::b);
        }
    }

    SECTION("Constexpr")
    {
        SECTION("!= Bitfield")
        {
            static constexpr auto false_val = []() {
                return EnumBitfield<Bits>{Bits::a} != EnumBitfield<Bits>{Bits::a};
            }();

            static constexpr auto true_val = []() {
                return EnumBitfield<Bits>{Bits::a} != EnumBitfield<Bits>{Bits::b};
            }();

            REQUIRE(true_val);
            REQUIRE_FALSE(false_val);
        }

        SECTION("!= enum")
        {
            static constexpr auto false_val = []() {
                return EnumBitfield<Bits>{Bits::a} != Bits::a;
            }();

            static constexpr auto true_val = []() {
                return EnumBitfield<Bits>{Bits::a} != Bits::b;
            }();

            REQUIRE(true_val);
            REQUIRE_FALSE(false_val);
        }
    }
}
