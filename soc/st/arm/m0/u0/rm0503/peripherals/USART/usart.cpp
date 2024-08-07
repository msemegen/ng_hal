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
using namespace soc::st::arm::m0::u0::rm0503::clocks;
using namespace soc::st::arm::m0::u0::rm0503::oscillators;
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

template<usart::Id id_t> std::uint32_t get_usart_source_freq_Hz()
{
    if (true == usart::clock::is_source_selected<id_t, sysclk>())
    {
        return sysclk::get_frequency_Hz();
    }
    if (true == usart::clock::is_source_selected<id_t, pclk>())
    {
        return pclk::get_frequency_Hz();
    }
    if (true == usart::clock::is_source_selected<id_t, lse>())
    {
        return lse::get_frequency_Hz();
    }
    if (true == usart::clock::is_source_selected<id_t, hsi16>())
    {
        return hsi16::get_frequency_Hz();
    }

    return 0;
}

std::uint32_t get_source_freq_Hz(usart::Id id_a)
{
#if defined XMCU_USART1_PRESENT
    if (usart::Id::_1 == id_a)
    {
        return get_usart_source_freq_Hz<usart::_1>();
    }
#endif
#if defined XMCU_USART2_PRESENT
    if (usart::Id::_2 == id_a)
    {
        return get_usart_source_freq_Hz<usart::_2>();
    }
#endif
#if defined XMCU_USART3_PRESENT
    if (usart::Id::_3 == id_a)
    {
        return get_usart_source_freq_Hz<usart::_3>();
    }
#endif
#if defined XMCU_USART4_PRESENT
    if (usart::Id::_4 == id_a)
    {
        return get_usart_source_freq_Hz<usart::_4>();
    }
#endif

    return 0u;
}

} // namespace

extern "C" {
using namespace soc::st::arm;
using namespace soc::st::arm::m0::u0::rm0503::peripherals;

#if defined XMCU_USART1_PRESENT
void USART1_IRQHandler()
{
    usart_isr_handler(reinterpret_cast<usart::Transceiver<api::traits::async>*>(USART1_BASE));
}
#endif
#if defined XMCU_USART2_PRESENT
void USART2_LPUART2_IRQHandler()
{
    usart_isr_handler(reinterpret_cast<usart::Transceiver<api::traits::async>*>(USART2_BASE));
}
#endif
#if defined XMCU_USART3_PRESENT
void USART3_LPUART1_IRQHandler()
{
    usart_isr_handler(reinterpret_cast<usart::Transceiver<api::traits::async>*>(USART3_BASE));
}
#endif
#if defined XMCU_USART4_PRESENT
void USART4_LPUART3_IRQHandler()
{
    usart_isr_handler(reinterpret_cast<usart::Transceiver<api::traits::async>*>(USART4_BASE));
}
#endif
}

namespace soc::st::arm::m0::u0::rm0503::peripherals {
using namespace xmcu;

void usart_isr_handler(usart::Transceiver<api::traits::async>* p_handler_a)
{
    const std::uint32_t isr = p_handler_a->isr;
    const std::uint32_t cr1 = p_handler_a->cr1;

    const usart::Error errors =
        static_cast<usart::Error>(xmcu::bit::flag::get(isr, USART_ISR_FE | USART_ISR_NE | USART_ISR_ORE | USART_ISR_PE));

    if (usart::Error::none != errors)
    {
        bit::flag::set(&(p_handler_a->icr), USART_ICR_FECF | USART_ICR_NECF | USART_ICR_ORECF | USART_ICR_PECF);
    }

    if (true == bit::flag::is(p_handler_a->cr1, USART_CR1_RXNEIE_RXFNEIE) &&
        (true == bit::flag::is(p_handler_a->isr, USART_ISR_RXNE_RXFNE) || usart::Error::none != errors))
    {
        usart::Transceiver<api::traits::async>::handler::on_receive(p_handler_a->rdr, errors, p_handler_a);
    }

    if (true == bit::flag::is(p_handler_a->isr, USART_ISR_TXE_TXFNF) && true == bit::flag::is(p_handler_a->cr1, USART_CR1_TXEIE_TXFNFIE))
    {
        const std::uint32_t r = usart::Transceiver<api::traits::async>::handler::on_transmit(p_handler_a);

        if (usart::Transceiver<api::traits::async>::no_data_to_transmit != r)
        {
            p_handler_a->tdr = r;
        }
    }

    if (true == bit::is_any(cr1, USART_CR1_IDLEIE | USART_CR1_TCIE | USART_CR1_CMIE) &&
        (bit::is_any(isr, USART_ISR_IDLE | USART_ISR_TC | USART_ISR_CMF) || usart::Error::none != errors))
    {
        usart::Event events = usart::Event::none;

        if (true == bit::flag::is(cr1, USART_CR1_IDLEIE) && true == bit::flag::is(isr, USART_ISR_IDLE))
        {
            events |= usart::Event::idle;
        }
        if (true == bit::flag::is(cr1, USART_CR1_TCIE) && true == bit::flag::is(isr, USART_ISR_TC))
        {
            events |= usart::Event::transfer_complete;
        }
        if (true == bit::flag::is(cr1, USART_CR1_CMIE) && true == bit::flag::is(isr, USART_ISR_CMF))
        {
            events |= usart::Event::character_matched;
        }

        bit::flag::set(&(p_handler_a->icr), USART_ICR_IDLECF | USART_ICR_TCCF | USART_ICR_CMCF);
        usart::Transceiver<api::traits::async>::handler::on_event(events, errors, p_handler_a);
    }
}

void usart::Peripheral::set_descriptor(const Descriptor& descriptor_a)
{
#ifndef NDEBUG
    constexpr std::uint32_t brr_min = 0x10u;
    constexpr std::uint32_t brr_max = 0xFFFFu;
#endif

    this->cr1 = 0x0u;
    this->cr2 = 0x0u;
    this->cr3 = 0x0u;
    this->presc = static_cast<std::uint32_t>(descriptor_a.prescaler);

    if (0x0u == (0xFFFFFFFFu & descriptor_a.baudrate))
    {
        const std::uint32_t baudrate = static_cast<std::uint32_t>((static_cast<std::uint64_t>(descriptor_a.baudrate) >> 32u));
        const std::uint32_t clk_freq_Hz = get_source_freq_Hz(this->get_id());
        assert(0x0u != baudrate);
        switch (descriptor_a.oversampling)
        {
            case usart::Oversampling::_8: {
                std::uint32_t div =
                    ((((clk_freq_Hz / clock_prescaler_lut[static_cast<std::uint32_t>(descriptor_a.prescaler)]) * 2u) + (baudrate / 2u)) /
                     baudrate);
#ifndef NDEBUG
                assert(div >= brr_min && div <= brr_max);
#endif
                std::uint16_t brr = static_cast<std::uint16_t>(div & 0xFFF0u);
                brr |= static_cast<std::uint16_t>((div & 0xFu) >> 1u);
                this->brr = brr;
            }
            break;

            case usart::Oversampling::_16: {
                std::uint32_t div =
                    ((clk_freq_Hz / clock_prescaler_lut[static_cast<std::uint32_t>(descriptor_a.prescaler)] + (baudrate / 2u)) / baudrate);
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

usart::Id usart::Peripheral::get_id() const
{
    std::uintptr_t address = reinterpret_cast<std::uintptr_t>(this);

#if defined XMCU_USART1_PRESENT
    if (address == USART1_BASE)
    {
        return Id::_1;
    }
#endif
#if defined XMCU_USART2_PRESENT
    if (address == USART2_BASE)
    {
        return Id::_2;
    }
#endif
#if defined XMCU_USART3_PRESENT
    if (address == USART3_BASE)
    {
        return Id::_3;
    }
#endif
#if defined XMCU_USART3_PRESENT
    if (address == USART4_BASE)
    {
        return Id::_4;
    }
#endif

    assert(false);
    return static_cast<Id>(std::numeric_limits<std::underlying_type<Id>::type>::max());
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
void usart::Transceiver<api::traits::async>::disable()
{
    IRQn_Type irq_type = select_irq(reinterpret_cast<std::uint32_t>(this));
    NVIC_DisableIRQ(irq_type);
}

void usart::Transceiver<api::traits::async>::receive_start()
{
    bit::flag::set(&(this->cr1), USART_CR1_RXNEIE_RXFNEIE | USART_CR1_PEIE);
    bit::flag::set(&(this->cr3), USART_CR3_EIE);
}
void usart::Transceiver<api::traits::async>::receive_stop()
{
    bit::flag::clear(&(this->cr1), USART_CR1_RXNEIE_RXFNEIE | USART_CR1_PEIE);
    bit::flag::clear(&(this->cr3), USART_CR3_EIE);
}

void usart::Transceiver<api::traits::async>::transmit_start()
{
    bit::flag::set(&(this->cr1), USART_CR1_TXEIE_TXFNFIE);
}
void usart::Transceiver<api::traits::async>::transmit_stop()
{
    bit::flag::clear(&(this->cr1), USART_CR1_TXEIE_TXFNFIE);
}

void usart::Transceiver<api::traits::async>::events_start(Event events_a)
{
    std::uint32_t enabled_events = 0x0u;

    if (Event::character_matched == (Event::character_matched & events_a))
    {
        enabled_events |= USART_CR1_CMIE;
    }
    if (Event::idle == (Event::idle & events_a))
    {
        enabled_events |= USART_CR1_IDLEIE;
    }
    if (Event::transfer_complete == (Event::transfer_complete & events_a))
    {
        enabled_events |= USART_CR1_TCIE;
    }

    bit::flag::set(&(this->cr1), enabled_events | USART_CR1_PEIE);
    bit::flag::set(&(this->cr3), USART_CR3_EIE);
}
void usart::Transceiver<api::traits::async>::events_stop()
{
    bit::flag::clear(&(this->cr1), USART_CR1_IDLEIE | USART_CR1_CMIE | USART_CR1_TCIE | USART_CR1_PEIE);
    bit::flag::clear(&(this->cr3), USART_CR3_EIE);
}

__WEAK void
usart::Transceiver<api::traits::async>::handler::on_receive(std::uint32_t word_a, Error errors_a, Transceiver<api::traits::async>* p_this)
{
}
__WEAK std::uint32_t usart::Transceiver<api::traits::async>::handler::on_transmit(Transceiver<api::traits::async>* p_this)
{
    return 0;
}
__WEAK void
usart::Transceiver<api::traits::async>::handler::on_event(Event events_a, Error errors_a, Transceiver<api::traits::async>* p_this)
{
}
} // namespace soc::st::arm::m0::u0::rm0503::peripherals
#endif