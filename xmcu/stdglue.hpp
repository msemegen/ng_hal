#pragma once

/*
 *	Name: stdglue.cpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <string_view>

// soc
#include <soc/st/arm/Systick.hpp>
#include <xmcu/non_constructible.hpp>

namespace xmcu {
struct stdglue : private xmcu::non_constructible
{
    struct assert : private non_constructible
    {
        struct handler : private non_constructible
        {
            static void output(std::string_view message_a, void* p_context_a);
            static void output(std::int32_t line_a, void* p_context_a);
        };

        static void set_context(void* p_context_a);
    };

    struct steady_clock : private non_constructible
    {
        static void set_source(soc::st::arm::systick::Tick_counter<soc::st::arm::api::traits::async>* p_clock_a);
    };
};
} // namespace xmcu