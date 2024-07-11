#if XMCU_SOC_VENDOR == st && XMCU_SOC_ARCH == arm

/*
    Name: stdglue.cpp

 */

// std
#include <cassert>
#include <chrono>

//
#include <soc/st/arm/Systick.hpp>
#include <soc/st/arm/stdglue.hpp>

namespace {
using namespace soc;
using namespace soc::st::arm;

volatile std::uint64_t systick_count = 0x0u;
std::uint32_t prescaler = 0x0u;
std::uint64_t xyz = 0x0u;
volatile std::uint64_t high_ticks = 0x0u;

systick::Tick_counter<api::traits::async>* p_timer = nullptr;
constexpr std::uint64_t nanosceconds_in_millisecond = 1000000ull;

#ifndef NDEBUG
stdglue::assert::Halt_handler assert_halt_handler;
stdglue::assert::Output_handler assert_output_handler;
#endif

extern "C" {
void __assert_func(const char*, int, const char*, const char*)
{
#ifndef NDEBUG
#endif
    while (true) continue;
}
}

} // namespace

namespace soc::st::arm {
#if 1 == XMCU_ISR_CONTEXT
void Systick::Peripheral<api::traits::async>::handler::reload(Systick::Controller<api::traits::async>* p_systick_a, void* p_context_a)
{
    systick_count++;
    high_ticks = (systick_count + p_timer->get_reload()) * p_systick_a->get_reload() * prescaler;
}
#endif

#if 0 == XMCU_ISR_CONTEXT
void systick::Tick_counter
<api::traits::async>::isr::reload(systick::Tick_counter<api::traits::async>* p_systick_a)
{
    systick_count = systick_count + 1u;
    high_ticks = (systick_count + p_timer->get_reload()) * p_systick_a->get_reload() * prescaler;
}
#endif

void stdglue::assert::set_handlers(const Output_handler& output_handler_a, const Halt_handler& halt_handler_a)
{
#ifndef NDEBUG
    assert_halt_handler = halt_handler_a;
    assert_output_handler = output_handler_a;
#endif
}

void stdglue::steady_clock::set_source(systick::Tick_counter<api::traits::async>* p_clock_a)
{
    p_timer = p_clock_a;
    prescaler = (nanosceconds_in_millisecond / (p_timer->get_reload() + 1u));
    xyz = prescaler * p_timer->get_reload();
}
} // namespace soc::st::arm

namespace std::chrono {
steady_clock::time_point steady_clock::now() noexcept
{
    volatile std::uint64_t high_ticks_temp = high_ticks;
    std::uint32_t val = p_timer->get_value();

    if (high_ticks_temp != high_ticks)
    {
        high_ticks_temp = high_ticks;
        val = p_timer->get_value();
    }

    return time_point(duration((high_ticks_temp - val * prescaler)));
}
} // namespace std::chrono
#endif