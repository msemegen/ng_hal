#pragma once

/*
 *	Name: api.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>

// xmcu
#include <xmcu/non_constructible.hpp>

namespace soc::st::arm {
struct api : private xmcu::non_constructible
{
    template<typename Type_a> static constexpr auto interface() = delete;

    enum class traits
    {
        sync = 0x1u,
        async = 0x2u
    };
};
} // namespace soc::st::arm
