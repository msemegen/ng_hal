/*
 *	Name: usart.cpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#if XMCU_SOC_ARCH_CORE_FAMILY == m0 && XMCU_SOC_VENDOR_FAMILY == stm32u0 && XMCU_SOC_VENDOR_FAMILY_RM == rm0503

// soc
#include <soc/st/arm/m0/u0/rm0503/peripherals/USART/usart.hpp>

namespace {
using namespace xmcu;
using namespace soc::st::arm;
using namespace soc::st::arm::m0::u0::rm0503::peripherals;

constexpr std::uint32_t clock_prescaler_lut[] = { 1u, 2u, 4u, 6u, 8u, 10u, 12u, 16u, 32u, 64u, 128u, 256u };

IRQn_Type select_irq(std::uint32_t base_address_a)
{
    switch (base_address_a)
    {
#if defined XMCU_USART1_PRESENT
        case USART1_BASE:
            return USART1_IRQn;
#endif
#if defined XMCU_USART2_PRESENT
        case USART2_BASE:
            return USART2_LPUART2_IRQn;
#endif
#if defined XMCU_USART3_PRESENT
        case USART3_BASE:
            return USART3_LPUART1_IRQn;
#endif
#if defined XMCU_USART4_PRESENT
        case USART4_BASE:
            return USART4_LPUART3_IRQn;
#endif
    }

    assert(false);
    return static_cast<IRQn_Type>(0xFFFFFFFF);
}

void usart_isr_handler(USART_TypeDef* p_registers_a, usart::Transceiver<api::traits::async>* p_handler_a)
{
    const std::uint32_t isr = p_registers_a->ISR;
    const std::uint32_t cr1 = p_registers_a->CR1;

    if (true == bit::flag::is(p_registers_a->ISR, USART_ISR_RXNE_RXFNE) &&
        true == bit::flag::is(p_registers_a->CR1, USART_CR1_RXNEIE_RXFNEIE))
    {
        usart::Transceiver<api::traits::async>::isr::on_read(p_registers_a->RDR, p_handler_a);
    }

    if (true == bit::flag::is(p_registers_a->ISR, USART_ISR_TXE_TXFNF) &&
        true == bit::flag::is(p_registers_a->CR1, USART_CR1_TXEIE_TXFNFIE))
    {
        p_registers_a->TDR = usart::Transceiver<api::traits::async>::isr::on_write(p_handler_a);
    }
}
} // namespace

extern "C" {
using namespace soc::st::arm;
using namespace soc::st::arm::m0::u0::rm0503::peripherals;

#if defined XMCU_USART1_PRESENT
void USART1_IRQHandler()
{
    usart_isr_handler(USART1, reinterpret_cast<usart::Transceiver<api::traits::async>*>(USART1_BASE));
}
#endif
#if defined XMCU_USART2_PRESENT
void USART2_LPUART2_IRQHandler()
{
    usart_isr_handler(USART2, reinterpret_cast<usart::Transceiver<api::traits::async>*>(USART2_BASE));
}
#endif
#if defined XMCU_USART3_PRESENT
void USART3_LPUART1_IRQHandler()
{
    usart_isr_handler(USART3, reinterpret_cast<usart::Transceiver<api::traits::async>*>(USART3_BASE));
}
#endif
#if defined XMCU_USART4_PRESENT
void USART4_LPUART3_IRQHandler()
{
    usart_isr_handler(USART4, reinterpret_cast<usart::Transceiver<api::traits::async>*>(USART4_BASE));
}
#endif
}

namespace soc::st::arm::m0::u0::rm0503::peripherals {
using namespace xmcu;

void usart::Peripheral::set_descriptor(const Descriptor& descriptor_a)
{
    assert(0x0 != descriptor_a.clock.clk_freq_Hz);

#ifndef NDEBUG
    constexpr std::uint32_t brr_min = 0x10u;
    constexpr std::uint32_t brr_max = 0xFFFFu;
#endif

    this->cr1 = 0x0u;
    this->cr2 = 0x0u;
    this->cr3 = 0x0u;

    this->presc = static_cast<std::uint32_t>(descriptor_a.clock.prescaler);

    if (0x0u == (0xFFFFFFFFu & descriptor_a.baudrate))
    {
        const std::uint32_t baudrate = static_cast<std::uint32_t>((static_cast<std::uint64_t>(descriptor_a.baudrate) >> 32u));
        assert(0x0u != baudrate);
        switch (descriptor_a.oversampling)
        {
            case usart::Descriptor::Oversampling::_8: {
                std::uint32_t div =
                    ((((descriptor_a.clock.clk_freq_Hz / clock_prescaler_lut[static_cast<std::uint32_t>(descriptor_a.clock.prescaler)]) *
                       2u) +
                      (baudrate / 2u)) /
                     baudrate);
#ifndef NDEBUG
                assert(div >= brr_min && div <= brr_max);
#endif
                std::uint16_t brr = static_cast<std::uint16_t>(div & 0xFFF0u);
                brr |= static_cast<std::uint16_t>((div & 0xFu) >> 1u);
                this->brr = brr;
            }
            break;

            case usart::Descriptor::Oversampling::_16: {
                std::uint32_t div =
                    ((descriptor_a.clock.clk_freq_Hz / clock_prescaler_lut[static_cast<std::uint32_t>(descriptor_a.clock.prescaler)] +
                      (baudrate / 2u)) /
                     baudrate);
#ifndef NDEBUG
                assert(div >= brr_min && div <= brr_max);
#endif
                this->brr = static_cast<std::uint16_t>(div);
            }
            break;
        }
    }

    bit::flag::set(&(this->cr1),
                   static_cast<std::uint32_t>(descriptor_a.fifo) | static_cast<std::uint32_t>(descriptor_a.oversampling) |
                       static_cast<std::uint32_t>(descriptor_a.mute) | static_cast<std::uint32_t>(descriptor_a.frame.parity) |
                       static_cast<std::uint32_t>(descriptor_a.frame.word_length));
    bit::flag::set(&(this->cr2),
                   (static_cast<std::uint32_t>(descriptor_a.mute) & 0xFF) | static_cast<std::uint32_t>(descriptor_a.baudrate) |
                       static_cast<std::uint32_t>(descriptor_a.frame.stop_bits) | static_cast<std::uint32_t>(descriptor_a.frame.msb_first) |
                       static_cast<std::uint32_t>(descriptor_a.frame.inversion));
    bit::flag::set(&(this->cr3), static_cast<std::uint32_t>(descriptor_a.sampling));
}

bool usart::Peripheral::enable(Mode mode_a, Stop_mode_activity stop_mode_activity, std::chrono::milliseconds timeout_a)
{
    bit::flag::set(&(this->cr1), USART_CR1_UESM, static_cast<std::uint32_t>(stop_mode_activity));
    bit::flag::set(&(this->cr1), static_cast<std::uint32_t>(mode_a) | USART_CR1_UE);
    bit::flag::set(&(this->icr), USART_ICR_TCCF | USART_ICR_IDLECF);

    return bit::wait_for::all_set(this->isr,
                                  (usart::Mode::rx == (mode_a & usart::Mode::rx) ? USART_ISR_REACK : 0x0u) |
                                      (usart::Mode::tx == (mode_a & usart::Mode::tx) ? USART_ISR_TEACK : 0x0u),
                                  timeout_a);
}
bool usart::Peripheral::disable(std::chrono::milliseconds timeout_a)
{
    bit::flag::clear(&(this->cr1), USART_CR1_TE | USART_CR1_RE | USART_CR1_UE | USART_CR1_UESM);
    return bit::wait_for::all_cleared(this->isr, USART_ISR_REACK | USART_ISR_TEACK, timeout_a);
}

#if 1 == XMCU_ISR_CONTEXT
void usart::Transceiver<api::traits::async>::enable(const IRQ_priority& priority_a, void* p_context_a)
#endif
#if 0 == XMCU_ISR_CONTEXT
    void usart::Transceiver<api::traits::async>::enable(const IRQ_priority& priority_a)
#endif
{
    IRQn_Type irq_type = select_irq(reinterpret_cast<std::uint32_t>(this));

    NVIC_EnableIRQ(irq_type);
    NVIC_SetPriority(irq_type, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), priority_a.preempt_priority, priority_a.sub_priority));
}
void usart::Transceiver<api::traits::async>::disable() {}

void usart::Transceiver<api::traits::async>::read_start()
{
    bit::flag::set(&(this->cr1), USART_CR1_RXNEIE_RXFNEIE);
}
void usart::Transceiver<api::traits::async>::read_stop()
{
    bit::flag::clear(&(this->cr1), USART_CR1_RXNEIE_RXFNEIE);
}

void usart::Transceiver<api::traits::async>::write_start()
{
    bit::flag::set(&(this->cr1), USART_CR1_TXEIE_TXFNFIE);
}
void usart::Transceiver<api::traits::async>::write_stop()
{
    bit::flag::clear(&(this->cr1), USART_CR1_TXEIE_TXFNFIE);
}

__WEAK void usart::Transceiver<api::traits::async>::isr::on_read(std::uint32_t word_a, usart::Transceiver<api::traits::async>* p_this) {}
__WEAK std::uint32_t usart::Transceiver<api::traits::async>::isr::on_write(usart::Transceiver<api::traits::async>* p_this)
{
    return 0;
}
__WEAK void usart::Transceiver<api::traits::async>::isr::on_error(usart::Error errors_a, usart::Transceiver<api::traits::async>* p_this) {}
} // namespace soc::st::arm::m0::u0::rm0503::peripherals
#endif