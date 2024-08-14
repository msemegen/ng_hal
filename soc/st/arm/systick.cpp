/*
 *	Name: systick.cpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#if XMCU_SOC_VENDOR == st && XMCU_SOC_ARCH == arm

// std
#include <cassert>
#include <tuple>

// soc/st
#include <soc/st/arm/systick.hpp>

namespace {
using namespace soc;
using namespace soc::st::arm;

#if 1 == XMCU_ISR_CONTEXT
void* p_context = nullptr;
#endif

extern "C" {
void SysTick_Handler()
{
#if 1 == XMCU_ISR_CONTEXT
    systick::Tick_counter<api::traits::async>::isr::on_reload(
        reinterpret_cast<systick::Tick_counter<api::traits::async>*>(SysTick_BASE), SysTick->VAL, p_context);
#endif

#if 0 == XMCU_ISR_CONTEXT
    systick::Tick_counter<api::traits::async>::isr::on_reload(
        reinterpret_cast<systick::Tick_counter<api::traits::async>*>(SysTick_BASE), SysTick->VAL);
#endif
}
}
} // namespace

namespace soc::st::arm {
using namespace xmcu;

using namespace soc;

#if 1 == XMCU_ISR_CONTEXT
__WEAK void systick::Tick_counter<api::traits::async>::isr::on_reload(systick::Tick_counter<api::traits::async>* p_systick_a,
                                                                      std::uint32_t value_a,
                                                                      void* p_context_a)
{
}
#endif

#if 0 == XMCU_ISR_CONTEXT
__WEAK void
systick::Tick_counter<api::traits::async>::isr::on_reload(systick::Tick_counter<api::traits::async>* p_systick_a, std::uint32_t value_a)
{
}
#endif

#if 1 == XMCU_ISR_CONTEXT
void systick::Tick_counter<api::traits::async>::start(const IRQ_priority& priority_a, void* p_context_a)
#endif
#if 0 == XMCU_ISR_CONTEXT
    void systick::Tick_counter<api::traits::async>::start(const IRQ_priority& priority_a)
#endif
{
#if 1 == XMCU_ISR_CONTEXT
    p_context = p_context_a;
#endif
    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), priority_a.preempt_priority, priority_a.sub_priority));

    bit::flag::set(&(this->ctrl), SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
}

void systick::Tick_counter<api::traits::async>::stop()
{
    bit::flag::clear(&(this->ctrl), SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);

#if 1 == XMCU_ISR_CONTEXT
    p_context = nullptr;
#endif
}
} // namespace soc::st::arm
#endif
