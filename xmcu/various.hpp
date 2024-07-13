#pragma once

/*
 *	Name: various.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>
#include <limits>
#include <type_traits>

// xmcu
#include <xmcu/Non_constructible.hpp>

namespace xmcu {
struct various : private non_constructible
{
    template<typename Type_t, std::size_t count> constexpr static std::size_t countof(Type_t (&arr)[count])
    {
        return std::extent<Type_t[count]>::value;
    }
    template<typename t_enum_type> constexpr static std::underlying_type_t<t_enum_type> to_underlying(t_enum_type a_enum)
    {
        return static_cast<std::underlying_type_t<t_enum_type>>(a_enum);
    }
};
} // namespace xmcu
