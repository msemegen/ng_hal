#pragma once

/*
 *  Name: Limited.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cassert>

namespace xmcu {
template<typename Type_t, Type_t minimum_t, Type_t maximum_t> class Limited
{
    static_assert(maximum_t >= minimum_t);

public:
    constexpr Limited()
        : value(minimum_t)
    {
    }

    Limited(const Limited& other_a)
        : value(other_a.value)
    {
    }

    Limited(Limited&& other_a)
        : value(other_a.value)
    {
    }

    Limited(Type_t value_a)
        : value(value_a)
    {
        assert(this->value >= minimum_t && this->value <= maximum_t);
    }

    Limited& operator=(const Limited& other_a)
    {
        if (this != &(other_a))
        {
            this->value = other_a.value;
        }

        return *this;
    }

    operator Type_t()
    {
        return this->value;
    }
    operator Type_t() const
    {
        return this->value;
    }

    constexpr Type_t get() const
    {
        return this->value;
    }

private:
    Type_t value;
};
} // namespace xmcu
