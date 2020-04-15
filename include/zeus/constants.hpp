#pragma once

namespace zeus
{
    template<typename T>
    struct constants
    {
        T e{static_cast<T>(2.71828182845904523536)};
        T log_2_e{static_cast<T>(1.44269504088896340736)};
        T ln_2{static_cast<T>(0.693147180559945309417)};
        T ln_10{static_cast<T>(2.30258509299404568402)};
        T pi{static_cast<T>(3.14159265358979323846)};
        T pi_by_2{static_cast<T>(1.57079632679489661923)};
        T pi_by_4{static_cast<T>(0.785398163397448309616)};
        T one_by_pi{static_cast<T>(0.318309886183790671538)};
        T two_by_pi{static_cast<T>(0.636619772367581343076)};
        T two_by_sqrt_pi{static_cast<T>(1.12837916709551257390)};
        T sqrt_2{static_cast<T>(1.41421356237309504880)};
        T one_by_sqrt_2{static_cast<T>(0.707106781186547524401)};
    };
} // namespace zeus
