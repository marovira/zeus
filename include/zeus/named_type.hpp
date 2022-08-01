#pragma once

#include "crtp.hpp"

// This header defines a strong-typing interface along with a set of common
// operations taken from FluentC++
// https://www.fluentcpp.com/2017/05/23/strong-types-inheriting-functionalities-from-underlying/

namespace zeus
{
    template<typename T, typename Parameter, template<typename> class... Skills>
    class NamedType : public Skills<NamedType<T, Parameter, Skills...>>...
    {
    public:
        explicit NamedType(T val) :
            m_value{val}
        {}

        T& get()
        {
            return m_value;
        }

        T const& get() const
        {
            return m_value;
        }

    private:
        T m_value;
    };

    template<typename T>
    struct Addable : CRTPBase<T, Addable>
    {
        T& operator+=(T const& other)
        {
            this->self().get() += other.get();
            return this->self();
        }

        T operator+(T const& other) const
        {
            return T{this->self().get() + other.get()};
        }
    };

    template<typename T>
    struct Subtractable : CRTPBase<T, Subtractable>
    {
        T& operator-=(T const& other)
        {
            this->self().get() -= other.get();
            return this->self();
        }

        T operator-(T const& other) const
        {
            return T{this->self().get() - other.get()};
        }
    };

    template<typename T>
    struct Multiplicable : CRTPBase<T, Multiplicable>
    {
        T& operator*=(T const& other)
        {
            this->self().get() *= other.get();
            return this->self();
        }

        T operator*(T const& other) const
        {
            return T{this->self().get() * other.get()};
        }
    };

    template<typename T>
    struct Divisible : CRTPBase<T, Divisible>
    {
        T& operator/=(T const& other)
        {
            this->self().get() /= other.get();
            return this->self();
        }

        T operator/(T const& other) const
        {
            return T{this->self().get() / other.get()};
        }
    };
} // namespace zeus
