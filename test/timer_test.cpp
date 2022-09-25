#include <zeus/timer.hpp>

#include <catch2/catch_test_macros.hpp>
#include <thread>

TEST_CASE("[timer] - timer: elapsed", "[zeus]")
{
    using zeus::Timer;
    using namespace std::chrono_literals;

    Timer<double> t;
    t.start();
    std::this_thread::sleep_for(1s);
    auto elapsed{static_cast<int>(t.elapsed())};

    REQUIRE(elapsed == 1);
}

TEST_CASE("[timer] - Timer: split", "[zeus]")
{
    using zeus::Timer;
    using namespace std::chrono_literals;

    Timer<int> t;

    SECTION("Empty timer")
    {
        auto ret = t.split();

        REQUIRE(ret == 0);
    }

    SECTION("Started timer")
    {
        t.start();
        std::this_thread::sleep_for(1s);
        auto split = t.split();
        REQUIRE(split == 1);
    }

    SECTION("Multiple splits")
    {
        t.start();
        std::this_thread::sleep_for(1s);
        auto split = t.split();
        REQUIRE(split == 1);

        std::this_thread::sleep_for(1s);
        split        = t.split();
        auto elapsed = t.elapsed();
        REQUIRE(split == 1);
        REQUIRE(elapsed == 2);
    }
}
