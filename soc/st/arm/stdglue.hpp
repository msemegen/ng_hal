#pragma once

#include <soc/non_constructible.hpp>
#include <soc/st/arm/Systick.hpp>

namespace soc::st::arm {
struct stdglue : private non_constructible
{
    struct assert : private non_constructible
    {
        struct Output_handler
        {
        };

        struct Halt_handler
        {
        };

        void set_handlers(const Output_handler& output_handler_a, const Halt_handler& halt_handler_a);
    };

    struct steady_clock : private non_constructible
    {
        static void set_source(systick::Tick_counter<soc::st::arm::api::traits::async>* p_clock_a);
    };
};
} // namespace soc::st::arm