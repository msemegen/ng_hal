#pragma once

// std
#include <string_view>

// soc
#include <soc/non_constructible.hpp>
#include <soc/st/arm/Systick.hpp>

namespace soc::st::arm {
struct stdglue : private non_constructible
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
        static void set_source(systick::Tick_counter<soc::st::arm::api::traits::async>* p_clock_a);
    };
};
} // namespace soc::st::arm