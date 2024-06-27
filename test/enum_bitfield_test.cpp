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
    SECTION("Runtime")
    {
        SECTION("From enum")
        {
            EnumBitfield<Bits> field{Bits::a};
            REQUIRE(field.bits() == 1);
        }

        SECTION("From base type")
        {
            std::uint8_t flags = 0x01;
            EnumBitfield<Bits> field{flags};
            REQUIRE(field.bits() == flags);
        }
    }

    SECTION("Compile-time")
    {
        SECTION("From enum")
        {
            static constexpr auto val = []() {
                EnumBitfield<Bits> field{Bits::a};
                return field.bits();
            }();

            STATIC_REQUIRE(val == 1);
        }

        SECTION("From base type")
        {
            static constexpr auto val = []() {
                std::uint8_t flags = 0x01;
                EnumBitfield<Bits> field{flags};
                return field.bits();
            }();

            STATIC_REQUIRE(val == 1);
        }
    }
}

TEST_CASE("[EnumBitfield] - operator=", "[zeus]")
{
    SECTION("Runtime")
    {
        SECTION("From enum")
        {
            EnumBitfield<Bits> a;
            a = Bits::b;
            REQUIRE(a.bits() == 2);
        }

        SECTION("From base type")
        {
            EnumBitfield<Bits> a;
            a = 2;
            REQUIRE(a.bits() == 2);
        }
    }

    SECTION("Compile-time")
    {
        SECTION("From enum")
        {
            static constexpr auto val = []() {
                EnumBitfield<Bits> a;
                a = Bits::b;
                return a.bits();
            }();

            STATIC_REQUIRE(val == 2);
        }

        SECTION("From base type")
        {
            static constexpr auto val = []() {
                EnumBitfield<Bits> a;
                a = 2;
                return a.bits();
            }();

            STATIC_REQUIRE(val == 2);
        }
    }
}

TEST_CASE("[EnumBitfield] - value", "[zeus]")
{
    SECTION("Runtime")
    {
        EnumBitfield<Bits> a{Bits::a};
        REQUIRE(a.value() == Bits::a);
    }

    SECTION("Compile-time")
    {
        static constexpr auto val = []() {
            EnumBitfield<Bits> a{Bits::a};
            return a.value();
        }();

        STATIC_REQUIRE(val == Bits::a);
    }
}

TEST_CASE("[EnumBitfield] - operator&=", "[zeus]")
{
    SECTION("Runtime")
    {
        EnumBitfield<Bits> field{Bits::a};

        SECTION("&= Bitfield")
        {
            field &= EnumBitfield<Bits>{Bits::a};
            REQUIRE(field.bits() == 1);

            field &= EnumBitfield<Bits>{Bits::b};
            REQUIRE(field.bits() == 0);
        }

        SECTION("&= enum")
        {
            field &= Bits::a;
            REQUIRE(field.bits() == 1);

            field &= Bits::b;
            REQUIRE(field.bits() == 0);
        }
    }

    SECTION("Compile-time")
    {
        SECTION("&= Bitfield")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field &= EnumBitfield<Bits>{Bits::a};
                    return field.bits();
                }();

                STATIC_REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field &= EnumBitfield<Bits>{Bits::b};
                    return field.bits();
                }();

                STATIC_REQUIRE(val == 0);
            }
        }

        SECTION("&= enum")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field &= Bits::a;
                    return field.bits();
                }();

                STATIC_REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field &= Bits::b;
                    return field.bits();
                }();

                STATIC_REQUIRE(val == 0);
            }
        }
    }
}

TEST_CASE("[EnumBitfield] - operator|=", "[zeus]")
{
    SECTION("Runtime")
    {
        EnumBitfield<Bits> field{Bits::a};

        SECTION("|= Bitfield")
        {
            field |= EnumBitfield<Bits>{Bits::a};
            REQUIRE(field.bits() == 1);

            field |= EnumBitfield<Bits>{Bits::b};
            REQUIRE(field.bits() == 3);
        }

        SECTION("|= enum")
        {
            field |= Bits::a;
            REQUIRE(field.bits() == 1);

            field |= Bits::b;
            REQUIRE(field.bits() == 3);
        }
    }

    SECTION("Compile-time")
    {
        SECTION("|= Bitfield")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field |= EnumBitfield<Bits>{Bits::a};
                    return field.bits();
                }();

                STATIC_REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field |= EnumBitfield<Bits>{Bits::b};
                    return field.bits();
                }();

                STATIC_REQUIRE(val == 3);
            }
        }

        SECTION("|= enum")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field |= Bits::a;
                    return field.bits();
                }();

                STATIC_REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field |= Bits::b;
                    return field.bits();
                }();

                STATIC_REQUIRE(val == 3);
            }
        }
    }
}

TEST_CASE("[EnumBitfield] - operator^=", "[zeus]")
{
    SECTION("Runtime")
    {
        EnumBitfield<Bits> field{Bits::a};

        SECTION("^= Bitfield")
        {
            field ^= EnumBitfield<Bits>{Bits::a};
            REQUIRE(field.bits() == 0);

            field ^= EnumBitfield<Bits>{Bits::b};
            REQUIRE(field.bits() == 2);
        }

        SECTION("^= enum")
        {
            field ^= Bits::a;
            REQUIRE(field.bits() == 0);

            field ^= Bits::b;
            REQUIRE(field.bits() == 2);
        }
    }

    SECTION("Compile-time")
    {
        SECTION("^= Bitfield")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field ^= EnumBitfield<Bits>{Bits::a};
                    return field.bits();
                }();

                STATIC_REQUIRE(val == 0);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field ^= EnumBitfield<Bits>{Bits::b};
                    return field.bits();
                }();

                STATIC_REQUIRE(val == 3);
            }
        }

        SECTION("^= enum")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field ^= Bits::a;
                    return field.bits();
                }();

                STATIC_REQUIRE(val == 0);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    field ^= Bits::b;
                    return field.bits();
                }();

                STATIC_REQUIRE(val == 3);
            }
        }
    }
}

TEST_CASE("[EnumBitfield] - opeartor&", "[zeus]")
{
    SECTION("Runtime")
    {
        EnumBitfield<Bits> field{Bits::a};

        SECTION("& Bitfield")
        {
            auto val = field & EnumBitfield<Bits>{Bits::a};
            REQUIRE(val.bits() == 1);

            val = field & EnumBitfield<Bits>{Bits::b};
            REQUIRE(val.bits() == 0);
        }

        SECTION("& enum")
        {
            auto val = field & Bits::a;
            REQUIRE(val.bits() == 1);

            val = field & Bits::b;
            REQUIRE(val.bits() == 0);
        }
    }

    SECTION("Compile-time")
    {
        SECTION("& Bitfield")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field & EnumBitfield<Bits>{Bits::a}).bits();
                }();

                STATIC_REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field & EnumBitfield<Bits>{Bits::b}).bits();
                }();

                STATIC_REQUIRE(val == 0);
            }
        }

        SECTION("& enum")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field & Bits::a).bits();
                }();

                STATIC_REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field & Bits::b).bits();
                }();

                STATIC_REQUIRE(val == 0);
            }
        }
    }
}

TEST_CASE("[EnumBitfield] - operator|", "[zeus]")
{
    SECTION("Runtime")
    {
        EnumBitfield<Bits> field{Bits::a};

        SECTION("| Bitfield")
        {
            auto val = field | EnumBitfield<Bits>{Bits::a};
            REQUIRE(val.bits() == 1);

            val = field | EnumBitfield<Bits>{Bits::b};
            REQUIRE(val.bits() == 3);
        }

        SECTION("| enum")
        {
            auto val = field | Bits::a;
            REQUIRE(val.bits() == 1);

            val = field | Bits::b;
            REQUIRE(val.bits() == 3);
        }
    }

    SECTION("Compile-time")
    {
        SECTION("| Bitfield")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field | EnumBitfield<Bits>{Bits::a}).bits();
                }();

                STATIC_REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field | EnumBitfield<Bits>{Bits::b}).bits();
                }();

                STATIC_REQUIRE(val == 3);
            }
        }

        SECTION("| enum")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field | Bits::a).bits();
                }();

                STATIC_REQUIRE(val == 1);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field | Bits::b).bits();
                }();

                STATIC_REQUIRE(val == 3);
            }
        }
    }
}

TEST_CASE("[EnumBitfield] - opeartor^", "[zeus]")
{
    SECTION("Runtime")
    {
        EnumBitfield<Bits> field{Bits::a};

        SECTION("^ Bitfield")
        {
            auto val = field ^ EnumBitfield<Bits>{Bits::a};
            REQUIRE(val.bits() == 0);

            val = field ^ EnumBitfield<Bits>{Bits::b};
            REQUIRE(val.bits() == 3);
        }

        SECTION("^ enum")
        {
            auto val = field ^ Bits::a;
            REQUIRE(val.bits() == 0);

            val = field ^ Bits::b;
            REQUIRE(val.bits() == 3);
        }
    }

    SECTION("Compile-time")
    {
        SECTION("^ Bitfield")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field ^ EnumBitfield<Bits>{Bits::a}).bits();
                }();

                STATIC_REQUIRE(val == 0);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field ^ EnumBitfield<Bits>{Bits::b}).bits();
                }();

                STATIC_REQUIRE(val == 3);
            }
        }

        SECTION("^ enum")
        {
            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field ^ Bits::a).bits();
                }();

                STATIC_REQUIRE(val == 0);
            }

            {
                static constexpr auto val = []() {
                    EnumBitfield<Bits> field{Bits::a};
                    return (field ^ Bits::b).bits();
                }();

                STATIC_REQUIRE(val == 3);
            }
        }
    }
}

TEST_CASE("[EnumBitfield] - operator~", "[zeus]")
{
    SECTION("Runtime")
    {
        SECTION("Zero-bitfield")
        {
            auto val = ~EnumBitfield<Bits>{Bits::none};
            REQUIRE(val.bits() == 255);
        }

        SECTION("Non-zero bitfield")
        {
            auto val = ~EnumBitfield<Bits>{Bits::a};
            REQUIRE(val.bits() == 254);
        }
    }

    SECTION("Compile-time")
    {
        SECTION("Zero-bitfield")
        {
            static constexpr auto val = []() {
                return (~EnumBitfield<Bits>{Bits::none}).bits();
            }();
            STATIC_REQUIRE(val == 255);
        }

        SECTION("Non-zero bitfield")
        {
            static constexpr auto val = []() {
                return (~EnumBitfield<Bits>{Bits::a}).bits();
            }();
            STATIC_REQUIRE(val == 254);
        }
    }
}

TEST_CASE("[EnumBitfield] - operator>>", "[zeus]")
{
    SECTION("Runtime")
    {
        auto val = EnumBitfield<Bits>{Bits::b} >> 1;
        REQUIRE(val.bits() == 1);
    }

    SECTION("Compile-time")
    {
        static constexpr auto val = []() {
            return (EnumBitfield<Bits>{Bits::b} >> 1).bits();
        }();

        STATIC_REQUIRE(val == 1);
    }
}

TEST_CASE("[EnumBitfield] - operator<<", "[zeus]")
{
    SECTION("Runtime")
    {
        auto val = EnumBitfield<Bits>{Bits::a} << 1;
        REQUIRE(val.bits() == 2);
    }

    SECTION("Compile-time")
    {
        static constexpr auto val = []() {
            return (EnumBitfield<Bits>{Bits::a} << 1).bits();
        }();

        STATIC_REQUIRE(val == 2);
    }
}

TEST_CASE("[EnumBitfield] - operator bool", "[zeus]")
{
    SECTION("Runtime")
    {
        REQUIRE(EnumBitfield<Bits>{Bits::a});
        REQUIRE_FALSE(EnumBitfield<Bits>{Bits::none});
    }

    SECTION("Compile-time")
    {
        static constexpr auto true_val = []() -> bool {
            return EnumBitfield<Bits>{Bits::a};
        }();

        static constexpr auto false_val = []() -> bool {
            return EnumBitfield<Bits>{Bits::none};
        }();

        STATIC_REQUIRE(true_val);
        STATIC_REQUIRE_FALSE(false_val);
    }
}

TEST_CASE("[EnumBitfield] - operator==", "[zeus]")
{
    SECTION("Runtime")
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

    SECTION("Compile-time")
    {
        SECTION("== Bitfield")
        {
            static constexpr auto true_val = []() {
                return EnumBitfield<Bits>{Bits::a} == EnumBitfield<Bits>{Bits::a};
            }();

            static constexpr auto false_val = []() {
                return EnumBitfield<Bits>{Bits::a} == EnumBitfield<Bits>{Bits::b};
            }();

            STATIC_REQUIRE(true_val);
            STATIC_REQUIRE_FALSE(false_val);
        }

        SECTION("== enum")
        {
            static constexpr auto true_val = []() {
                return EnumBitfield<Bits>{Bits::a} == Bits::a;
            }();

            static constexpr auto false_val = []() {
                return EnumBitfield<Bits>{Bits::a} == Bits::b;
            }();

            STATIC_REQUIRE(true_val);
            STATIC_REQUIRE_FALSE(false_val);
        }
    }
}

TEST_CASE("[EnumBitfield] - opeartor!=", "[zeus]")
{
    SECTION("Runtime")
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

    SECTION("Compile-time")
    {
        SECTION("!= Bitfield")
        {
            static constexpr auto false_val = []() {
                return EnumBitfield<Bits>{Bits::a} != EnumBitfield<Bits>{Bits::a};
            }();

            static constexpr auto true_val = []() {
                return EnumBitfield<Bits>{Bits::a} != EnumBitfield<Bits>{Bits::b};
            }();

            STATIC_REQUIRE(true_val);
            STATIC_REQUIRE_FALSE(false_val);
        }

        SECTION("!= enum")
        {
            static constexpr auto false_val = []() {
                return EnumBitfield<Bits>{Bits::a} != Bits::a;
            }();

            static constexpr auto true_val = []() {
                return EnumBitfield<Bits>{Bits::a} != Bits::b;
            }();

            STATIC_REQUIRE(true_val);
            STATIC_REQUIRE_FALSE(false_val);
        }
    }
}

using namespace zeus::enum_bitwise_operators;

TEST_CASE("[enum_bitwise_operators] - operator&", "[zeus]")
{
    SECTION("Runtime")
    {
        auto field = Bits::a & Bits::a;
        REQUIRE(field.bits() == 1);

        field = Bits::a & Bits::b;
        REQUIRE(field.bits() == 0);
    }

    SECTION("Compile-time")
    {
        {
            static constexpr auto val = []() {
                return (Bits::a & Bits::a).bits();
            }();

            STATIC_REQUIRE(val == 1);
        }

        {
            static constexpr auto val = []() {
                return (Bits::a & Bits::b).bits();
            }();

            STATIC_REQUIRE(val == 0);
        }
    }
}

TEST_CASE("[enum_bitwise_operators] - operator|", "[zeus]")
{
    SECTION("Runtime")
    {
        auto field = Bits::a | Bits::b;
        REQUIRE(field.bits() == 3);
    }

    SECTION("Compile-time")
    {
        static constexpr auto val = []() {
            return (Bits::a | Bits::b).bits();
        }();

        STATIC_REQUIRE(val == 3);
    }
}

TEST_CASE("[enum_bitwise_operators] - operator^", "[zeus]")
{
    SECTION("Runtime")
    {
        auto field = Bits::a ^ Bits::b;
        REQUIRE(field.bits() == 3);
    }

    SECTION("Compile-time")
    {
        static constexpr auto val = []() {
            return (Bits::a ^ Bits::b).bits();
        }();

        STATIC_REQUIRE(val == 3);
    }
}

TEST_CASE("[enum_bitwise_operators] - operator~", "[zeus]")
{
    SECTION("Runtime")
    {
        auto field = ~Bits::a;
        REQUIRE(field.bits() == 254);
    }

    SECTION("Compile-time")
    {
        static constexpr auto val = []() {
            return (~Bits::a).bits();
        }();

        STATIC_REQUIRE(val == 254);
    }
}

TEST_CASE("[enum_bitwise_operators] - operator>>", "[zeus]")
{
    SECTION("Runtime")
    {
        auto field = Bits::b >> 1;
        REQUIRE(field.bits() == 1);
    }

    SECTION("Compile-time")
    {
        static constexpr auto val = []() {
            return (Bits::b >> 1).bits();
        }();

        STATIC_REQUIRE(val == 1);
    }
}

TEST_CASE("[enum_bitwise_operators] - operator<<", "[zeus]")
{
    SECTION("Runtime")
    {
        auto field = Bits::a << 1;
        REQUIRE(field.bits() == 2);
    }

    SECTION("Compile-time")
    {
        static constexpr auto val = []() {
            return (Bits::a << 1).bits();
        }();

        STATIC_REQUIRE(val == 2);
    }
}
