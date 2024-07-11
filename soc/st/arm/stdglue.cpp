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
void* p_assert_context = nullptr;
#endif
extern "C" {
void __assert_func(const char* p_file_a, int line_a, const char* p_function_a, const char* p_condition_a)
{
#ifndef NDEBUG
    stdglue::assert::handler::output(p_file_a, p_assert_context);

    __disable_irq();

#endif
    while (true) continue;
}
}

} // namespace

namespace soc::st::arm {
#if 1 == XMCU_ISR_CONTEXT
void systick::Tick_counter<api::traits::async>::isr::reload(systick::Tick_counter<api::traits::async>* p_systick_a, void*)
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

__WEAK void stdglue::assert::handler::output(std::string_view, void*) {}
__WEAK void stdglue::assert::handler::output(std::int32_t, void*) {}

void stdglue::assert::set_context(void* p_context_a)
{
#ifndef NDEBUG
    p_assert_context = p_context_a;
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