/*
 *	Name: stdglue.cpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#if XMCU_SOC_VENDOR == st && XMCU_SOC_ARCH == arm

// std
#include <cassert>
#include <chrono>
#include <sys/time.h>
#include <thread>
#include <unistd.h>

// soc
#include <soc/st/arm/Systick.hpp>

// xmcu
#include <xmcu/stdglue.hpp>

namespace {
using namespace soc;
using namespace soc::st::arm;

volatile std::uint64_t systick_count = 0x0u;

systick::Tick_counter<api::traits::async>* p_timer = nullptr;
std::uint64_t prescaler = 0u;
std::uint32_t current_val = 0u;
constexpr std::uint64_t parts_in_millisecond = 1000000ull;

#if 0 == XMCU_NOSTDLIB
std::uint32_t seconds = 0u;
volatile std::uint32_t high_ticks = 0x0u;
#endif

#if 1 == XMCU_NOSTDLIB
volatile std::uint64_t high_ticks = 0u;
#endif

#ifndef NDEBUG
void* p_assert_context = nullptr;
#endif

void delay(std::chrono::seconds timeout_a)
{
    const auto end = std::chrono::steady_clock::now() + timeout_a;
    while (end >= std::chrono::steady_clock::now()) continue;
}
#if 0 == XMCU_NOSTDLIB
void delay(std::chrono::microseconds timeout_a)
{
    const auto end = std::chrono::steady_clock::now() + timeout_a;
    while (end >= std::chrono::steady_clock::now()) continue;
}
#endif
#if 1 == XMCU_NOSTDLIB
void delay(std::chrono::nanoseconds timeout_a)
{
    const auto end = std::chrono::steady_clock::now() + timeout_a;
    while (end >= std::chrono::steady_clock::now()) continue;
}
#endif
} // namespace

namespace soc::st::arm {
#if 1 == XMCU_ISR_CONTEXT
void systick::Tick_counter<api::traits::async>::isr::on_reload(systick::Tick_counter<api::traits::async>* p_systick_a,
                                                               std::uint32_t value_a,
                                                               void*)
#endif
#if 0 == XMCU_ISR_CONTEXT
void systick::Tick_counter
<api::traits::async>::isr::on_reload(systick::Tick_counter<api::traits::async>* p_systick_a, std::uint32_t value_a)
#endif
{
    current_val = value_a;
    systick_count = systick_count + 1u;
#if 1 == XMCU_NOSTDLIB
    high_ticks = (systick_count + p_systick_a->get_descriptor().reload) * value_a * prescaler;
#endif
#if 0 == XMCU_NOSTDLIB
    std::uint32_t temp = systick_count / 1000u;

    if (temp != seconds)
    {
        high_ticks = 0u;
        seconds = temp;
    }

    high_ticks += (current_val * prescaler) / 1000u;
#endif
}
} // namespace soc::st::arm

namespace xmcu {
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
    prescaler = (parts_in_millisecond / (p_timer->get_descriptor().reload + 1u));
}
} // namespace xmcu

#if 1 == XMCU_NOSTDLIB
namespace std::chrono {
steady_clock::time_point steady_clock::now() noexcept
{
    volatile std::uint64_t high_ticks_temp = high_ticks;

    if (high_ticks_temp != high_ticks)
    {
        high_ticks_temp = high_ticks;
    }

    return time_point(duration((high_ticks_temp - current_val * prescaler)));
}
} // namespace std::chrono

namespace std::this_thread {
void __sleep_for(chrono::seconds seconds_a, chrono::nanoseconds nanoseconds_a)
{
    delay(seconds_a);
    delay(nanoseconds_a);
}
} // namespace std::this_thread
#endif
extern "C" {
using namespace xmcu;

void __assert_func(const char* p_file_a, int line_a, const char* p_function_a, const char* p_condition_a)
{
#ifndef NDEBUG
    __disable_irq();

    stdglue::assert::handler::output("\r\n", p_assert_context);
    stdglue::assert::handler::output(p_file_a, p_assert_context);
    stdglue::assert::handler::output("(", p_assert_context);
    stdglue::assert::handler::output(line_a, p_assert_context);
    stdglue::assert::handler::output("):", p_assert_context);
    stdglue::assert::handler::output(p_function_a, p_assert_context);
    stdglue::assert::handler::output(" -> ", p_assert_context);
    stdglue::assert::handler::output(p_condition_a, p_assert_context);
    stdglue::assert::handler::output("\n", p_assert_context);

    while (true) continue;
#endif
}

#if 0 == XMCU_NOSTDLIB
int _gettimeofday(struct timeval* p_time_val_a, void*)
{
    volatile std::uint64_t high_ticks_temp = high_ticks;

    if (high_ticks_temp != high_ticks)
    {
        high_ticks_temp = high_ticks;
    }

    p_time_val_a->tv_sec = seconds;
    p_time_val_a->tv_usec = high_ticks_temp;

    return 0;
}

int usleep(useconds_t timeout_a)
{
    delay(std::chrono::microseconds(timeout_a));
    return 0;
}
unsigned int sleep(unsigned int seconds_a)
{
    delay(std::chrono::seconds(seconds_a));
    return 0;
}
#endif
}
#endif