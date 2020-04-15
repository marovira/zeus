#include <zeus/timer.hpp>

#include <catch2/catch.hpp>
#include <thread>

TEST_CASE("[timer] - timer: elapsed", "[zeus]")
{
    using zeus::timer;
    using namespace std::chrono_literals;

    timer<double> t;
    t.start();
    std::this_thread::sleep_for(1s);
    auto elapsed{static_cast<int>(t.elapsed())};

    REQUIRE(elapsed == 1);
}
