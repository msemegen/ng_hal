/*
 *	Name: gpio.cpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#if XMCU_SOC_ARCH_CORE_FAMILY == m0 && XMCU_SOC_VENDOR_FAMILY == stm32u0 && XMCU_SOC_VENDOR_FAMILY_RM == rm0503

// soc
#include <soc/st/arm/m0/u0/rm0503/peripherals/GPIO/gpio.hpp>

namespace {
using namespace xmcu;
using namespace soc::st::arm::m0::u0::rm0503::peripherals;
extern "C" {
void EXTI0_1_IRQHandler()
{
    if (0x0u != EXTI->FPR1)
    {
        if (true == bit::is(EXTI->FPR1, 0u))
        {
            gpio::async::handler::on_fall(0u);
            bit::set(&(EXTI->FPR1), 0u);
        }
        if (true == bit::is(EXTI->FPR1, 1u))
        {
            gpio::async::handler::on_fall(1u);
            bit::set(&(EXTI->FPR1), 1u);
        }
    }

    if (0x0u != EXTI->RPR1)
    {
        if (true == bit::is(EXTI->RPR1, 0u))
        {
            gpio::async::handler::on_rise(0u);
            bit::set(&(EXTI->RPR1), 0u);
        }
        if (true == bit::is(EXTI->RPR1, 1u))
        {
            gpio::async::handler::on_rise(1u);
            bit::set(&(EXTI->RPR1), 1u);
        }
    }
}
void EXTI2_3_IRQHandler()
{
    if (0x0u != EXTI->FPR1)
    {
        if (true == bit::is(EXTI->FPR1, 2u))
        {
            gpio::async::handler::on_fall(2u);
            bit::set(&(EXTI->FPR1), 2u);
        }
        if (true == bit::is(EXTI->FPR1, 3u))
        {
            gpio::async::handler::on_fall(3u);
            bit::set(&(EXTI->FPR1), 3u);
        }
    }

    if (0x0u != EXTI->RPR1)
    {
        if (true == bit::is(EXTI->RPR1, 2u))
        {
            gpio::async::handler::on_rise(2u);
            bit::set(&(EXTI->RPR1), 2u);
        }
        if (true == bit::is(EXTI->RPR1, 3u))
        {
            gpio::async::handler::on_rise(3u);
            bit::set(&(EXTI->RPR1), 3u);
        }
    }
}
void EXTI4_15_IRQHandler()
{
    for (std::uint32_t i = 4; i <= 15; i++)
    {
        if (true == bit::is(EXTI->FPR1, i))
        {
            gpio::async::handler::on_fall(i);
            bit::set(&(EXTI->FPR1), i);
        }
        if (true == bit::is(EXTI->RPR1, i))
        {
            gpio::async::handler::on_rise(i);
            bit::set(&(EXTI->RPR1), i);
        }
    }
}
}
} // namespace

namespace soc::st::arm::m0::u0::rm0503::peripherals {
using namespace xmcu;

void gpio::configure_pin(ll::gpio::Registers* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::out>& desc_a)
{
    bit::flag::set(&(p_port_a->ospeedr), ll::gpio::OSPEEDR::mask << pin_a, static_cast<ll::gpio::OSPEEDR::Flag>(desc_a.speed) << pin_a);
    bit::flag::set(&(p_port_a->pupdr), ll::gpio::PUPDR::mask << pin_a, static_cast<ll::gpio::PUPDR::Flag>(desc_a.pull) << pin_a);
    bit::flag::set(&(p_port_a->otyper), ll::gpio::OTYPER::mask << pin_a, static_cast<ll::gpio::OTYPER::Flag>(desc_a.type) << pin_a);
    bit::flag::set(&(p_port_a->moder), ll::gpio::MODER::mask << pin_a, ll::gpio::MODER::output << pin_a);
}

void gpio::configure_pin(ll::gpio::Registers* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::in>& desc_a)
{
    bit::flag::set(&(p_port_a->pupdr), ll::gpio::PUPDR::mask << pin_a, static_cast<ll::gpio::PUPDR::Flag>(desc_a.pull) << pin_a);
    bit::flag::set(&(p_port_a->moder), ll::gpio::MODER::mask << pin_a, ll::gpio::MODER::input << pin_a);
}

void gpio::configure_pin(ll::gpio::Registers* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::analog>& desc_a)
{
    bit::flag::set(&(p_port_a->pupdr), ll::gpio::PUPDR::mask << pin_a, static_cast<ll::gpio::PUPDR::Flag>(desc_a.pull) << pin_a);
    bit::flag::set(&(p_port_a->moder), ll::gpio::MODER::mask << pin_a, ll::gpio::MODER::analog << pin_a);
}

void gpio::configure_pin(ll::gpio::Registers* p_port_a,
                         std::uint32_t pin_a,
                         std::uint32_t function_a,
                         const gpio::Descriptor<gpio::Mode::alternate>& desc_a)
{
    bit::flag::set(&(p_port_a->ospeedr), ll::gpio::OSPEEDR::mask << pin_a, static_cast<ll::gpio::OSPEEDR::Flag>(desc_a.speed) << pin_a);
    bit::flag::set(&(p_port_a->pupdr), ll::gpio::PUPDR::mask << pin_a, static_cast<ll::gpio::PUPDR::Flag>(desc_a.pull) << pin_a);
    bit::flag::set(&(p_port_a->otyper), ll::gpio::OTYPER::mask << pin_a, static_cast<ll::gpio::OTYPER::Flag>(desc_a.type) << pin_a);

    const std::uint32_t index = pin_a >> 3u;
    const std::uint32_t shift = pin_a - (index * 8u);

    assert(various::countof(p_port_a->afr) > index);

    bit::flag::set(&(p_port_a->afr[index]), ll::gpio::AFR::mask << shift, static_cast<ll::gpio::AFR::Flag>(function_a) << shift);
    bit::flag::set(&(p_port_a->moder), ll::gpio::MODER::mask << pin_a, ll::gpio::MODER::af << pin_a);
}

void gpio::async::enable(const IRQ_priority& priority_a)
{
    NVIC_EnableIRQ(IRQn_Type::EXTI0_1_IRQn);
    NVIC_EnableIRQ(IRQn_Type::EXTI2_3_IRQn);
    NVIC_EnableIRQ(IRQn_Type::EXTI4_15_IRQn);
    NVIC_SetPriority(IRQn_Type::EXTI0_1_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), priority_a.preempt_priority, priority_a.sub_priority));
    NVIC_SetPriority(IRQn_Type::EXTI2_3_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), priority_a.preempt_priority, priority_a.sub_priority));
    NVIC_SetPriority(IRQn_Type::EXTI4_15_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), priority_a.preempt_priority, priority_a.sub_priority));
}
void gpio::async::disable()
{
    NVIC_DisableIRQ(IRQn_Type::EXTI0_1_IRQn);
    NVIC_DisableIRQ(IRQn_Type::EXTI2_3_IRQn);
    NVIC_DisableIRQ(IRQn_Type::EXTI4_15_IRQn);
}

bool gpio::is_irq_slot_enabled(std::uint32_t port_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    const std::uint32_t idx = pin_a >> 2u;
    const std::uint32_t pos = pin_a % 4u;

    assert(various::countof(gpio::enabled_slots) > idx);

    return 0x0u != (gpio::enabled_slots[idx] & ((port_a) << (pos * 8u)));
}
void gpio::enable_irq_slot(std::uint32_t port_a, std::uint32_t pin_a, volatile std::uint32_t* p_array_a, std::size_t array_length_a)
{
    const std::uint32_t idx = pin_a >> 2u;
    const std::uint32_t pos = pin_a % 4u;

    assert(array_length_a > idx);

    p_array_a[idx] |= ((port_a) << (pos * 8u));
}
void gpio::disable_irq_slot(std::uint32_t port_a, std::uint32_t pin_a, volatile std::uint32_t* p_array_a, std::size_t array_length_a)
{
    const std::uint32_t idx = pin_a >> 2u;
    const std::uint32_t pos = pin_a % 4u;

    assert(array_length_a > idx);

    p_array_a[idx] &= ~((0xFFu) << (pos * 8u));
}
void gpio::set_irq_edge(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a, Edge edge_a)
{
    bit::clear(&(EXTI->RTSR1), pin_a);
    bit::clear(&(EXTI->FTSR1), pin_a);

    if (Edge::rising == (edge_a & Edge::rising))
    {
        bit::set(&(EXTI->RTSR1), pin_a);
    }

    if (Edge::falling == (edge_a & Edge::falling))
    {
        bit::set(&(EXTI->FTSR1), pin_a);
    }
}

__WEAK void gpio::async::handler::on_rise(std::uint32_t) {}
__WEAK void gpio::async::handler::on_fall(std::uint32_t) {}
} // namespace soc::st::arm::m0::u0::rm0503::peripherals
#endif