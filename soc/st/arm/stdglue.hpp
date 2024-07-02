#pragma once

#include <soc/non_constructible.hpp>
#include <soc/st/arm/Systick.hpp>

namespace soc::st::arm {
struct stdglue : private non_constructible
{
    static void set_steady_clock_source(systick::Handler<soc::st::arm::api::traits::async>* p_clock_a);
};
} // namespace soc::st::arm