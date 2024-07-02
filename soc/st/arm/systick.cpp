#if XMCU_SOC_VENDOR == st && XMCU_SOC_ARCH == arm

/*
 *	Name: systick.cpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <tuple>

// soc
#include <soc/assert.hpp>

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
    systick::Handler<api::traits::async>::isr::reload(
        reinterpret_cast<systick::Handler<api::traits::async>*>(SysTick_BASE), p_context);
#endif

#if 0 == XMCU_ISR_CONTEXT
    systick::Handler<api::traits::async>::isr::reload(
        reinterpret_cast<systick::Handler<api::traits::async>*>(SysTick_BASE));
#endif
}
}
} // namespace

namespace soc::st::arm {
using namespace soc;

#if 1 == XMCU_ISR_CONTEXT
__WEAK void systick::Handler<api::traits::async>::isr::reload(systick::Handler<traits::async>* p_systick_a, p_context)
{
}
#endif

#if 0 == XMCU_ISR_CONTEXT
__WEAK void
systick::Handler<api::traits::async>::isr::reload(systick::Handler<api::traits::async>* p_systick_a)
{
}
#endif

#if 1 == XMCU_ISR_CONTEXT
void systick::Handler<traits::async>::start(void* p_context_a)
#endif
#if 0 == XMCU_ISR_CONTEXT
    void systick::Handler<api::traits::async>::start()
#endif
{
#if 1 == XMCU_ISR_CONTEXT
    p_context = p_context_a;
#endif
    bit_flag::set(&(this->CTRL), SysTick_CTRL_TICKINT_Msk);
}

void systick::Handler<api::traits::async>::stop()
{
    bit_flag::clear(&(this->CTRL), SysTick_CTRL_TICKINT_Msk);

#if 1 == XMCU_ISR_CONTEXT
    p_context = nullptr;
#endif
}
} // namespace soc::st::arm
#endif
