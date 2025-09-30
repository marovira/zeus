#pragma once

namespace zeus
{
    // A CRTP base class taken from FluentC++
    // https://www.fluentcpp.com/2017/05/19/crtp-helper/
    template<typename T, template<typename> class CRTPType>
    class CRTPBase
    {
        CRTPBase() = default;
        friend CRTPType<T>;

    public:
        constexpr auto self() -> T&
        {
            return static_cast<T&>(*this);
        }

        constexpr auto self() const -> T const&
        {
            return static_cast<T const&>(*this);
        }
    };
} // namespace zeus
