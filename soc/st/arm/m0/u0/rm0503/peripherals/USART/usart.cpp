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
    const ll::usart::ISR::Data isr = p_handler_a->isr;
    const ll::usart::CR1::Data cr1 = p_handler_a->cr1;

    const usart::Error errors =
        static_cast<usart::Error>(bit::flag::get(isr, ll::usart::ISR::fe | ll::usart::ISR::ne | ll::usart::ISR::ore | ll::usart::ISR::pe));

    if (usart::Error::none != errors)
    {
        xmcu::bit::flag::set(&(p_handler_a->icr),
                             ll::usart::ICR::fecf | ll::usart::ICR::necf | ll::usart::ICR::orecf | ll::usart::ICR::pecf);
    }

    if (true == xmcu::bit::flag::is(cr1, ll::usart::CR1::rxneie) && true == xmcu::bit::flag::is(p_handler_a->isr, ll::usart::ISR::rxne) ||
        usart::Error::none != errors)
    {
        usart::Transceiver<api::traits::async>::handler::on_receive(p_handler_a->rdr, errors, p_handler_a);
    }

    if (true == bit::flag::is(p_handler_a->isr, ll::usart::ISR::txe) && true == bit::flag::is(p_handler_a->cr1, ll::usart::CR1::txeie))
    {
        const std::uint32_t r = usart::Transceiver<api::traits::async>::handler::on_transmit(p_handler_a);

        if (usart::Transceiver<api::traits::async>::no_data_to_transmit != r)
        {
            p_handler_a->tdr = r;
        }
    }

    if (true == bit::is_any(cr1, ll::usart::CR1::idleie | ll::usart::CR1::tcie | ll::usart::CR1::cmie) &&
        (bit::is_any(isr, ll::usart::ISR::idle | ll::usart::ISR::tc | ll::usart::ISR::cmf) || usart::Error::none != errors))
    {
        usart::Event events = usart::Event::none;

        if (true == bit::flag::is(cr1, ll::usart::CR1::idleie) && true == bit::flag::is(isr, ll::usart::ISR::idle))
        {
            events |= usart::Event::idle;
        }
        if (true == bit::flag::is(cr1, ll::usart::CR1::tcie) && true == bit::flag::is(isr, ll::usart::ISR::tc))
        {
            events |= usart::Event::transfer_complete;
        }
        if (true == bit::flag::is(cr1, ll::usart::CR1::cmie) && true == bit::flag::is(isr, ll::usart::ISR::cmf))
        {
            events |= usart::Event::character_matched;
        }

        bit::flag::set(&(p_handler_a->icr), ll::usart::ICR::idlecf | ll::usart::ICR::tccf | ll::usart::ICR::cmcf);
        usart::Transceiver<api::traits::async>::handler::on_event(events, errors, p_handler_a);
    }
}

void usart::Peripheral::set_descriptor(const Descriptor& descriptor_a)
{
#ifndef NDEBUG
    constexpr std::uint32_t brr_min = 0x10u;
    constexpr std::uint32_t brr_max = 0xFFFFu;
#endif

    this->cr1.zero();
    this->cr2.zero();
    this->cr3.zero();
    this->presc = static_cast<ll::usart::PRESC::Data>(descriptor_a.prescaler);

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
                   static_cast<ll::usart::CR1::Flag>(descriptor_a.fifo) | static_cast<ll::usart::CR1::Flag>(descriptor_a.oversampling) |
                       static_cast<ll::usart::CR1::Flag>(descriptor_a.mute) | static_cast<ll::usart::CR1::Flag>(descriptor_a.frame.parity) |
                       static_cast<ll::usart::CR1::Flag>(descriptor_a.frame.word_length));

    bit::flag::set(&(this->cr2),
                   static_cast<ll::usart::CR2::Flag>(descriptor_a.mute) |
                       static_cast<ll::usart::CR2::Flag>(static_cast<std::uint64_t>(descriptor_a.baudrate)) |
                       static_cast<ll::usart::CR2::Flag>(descriptor_a.frame.stop_bits) |
                       static_cast<ll::usart::CR2::Flag>(descriptor_a.frame.msb_first) |
                       static_cast<ll::usart::CR2::Flag>(descriptor_a.frame.inversion));
    bit::flag::set(&(this->cr3), static_cast<ll::usart::CR3::Flag>(descriptor_a.sampling));
}

bool usart::Peripheral::enable(Mode mode_a, Stop_mode_activity stop_mode_activity, std::chrono::milliseconds timeout_a)
{
    bit::flag::set(&(this->cr1), ll::usart::CR1::uesm, static_cast<ll::usart::CR1::Flag>(stop_mode_activity));
    bit::flag::set(&(this->cr1), static_cast<ll::usart::CR1::Flag>(mode_a) | ll::usart::CR1::ue);
    bit::flag::set(&(this->icr), ll::usart::ICR::tcbgtcf | ll::usart::ICR::idlecf);

    return bit::wait_for::all_set(this->isr,
                                  (usart::Mode::rx == (mode_a & usart::Mode::rx) ? ll::usart::ISR::reack : ll::usart::ISR::none) |
                                      (usart::Mode::tx == (mode_a & usart::Mode::tx) ? ll::usart::ISR::teack : ll::usart::ISR::none),
                                  timeout_a);
}
bool usart::Peripheral::disable(std::chrono::milliseconds timeout_a)
{
    bit::flag::clear(&(this->cr1), ll::usart::CR1::te | ll::usart::CR1::re | ll::usart::CR1::ue | ll::usart::CR1::uesm);
    return bit::wait_for::all_cleared(this->isr, ll::usart::ISR::reack | ll::usart::ISR::teack, timeout_a);
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
    bit::flag::set(&(this->cr1), ll::usart::CR1::rxneie | ll::usart::CR1::peie);
    bit::flag::set(&(this->cr3), ll::usart::CR3::eie);
}
void usart::Transceiver<api::traits::async>::receive_stop()
{
    bit::flag::clear(&(this->cr1), ll::usart::CR1::rxneie | ll::usart::CR1::peie);
    bit::flag::clear(&(this->cr3), ll::usart::CR3::eie);
}

void usart::Transceiver<api::traits::async>::transmit_start()
{
    bit::flag::set(&(this->cr1), ll::usart::CR1::txeie);
}
void usart::Transceiver<api::traits::async>::transmit_stop()
{
    bit::flag::clear(&(this->cr1), ll::usart::CR1::txeie);
}

void usart::Transceiver<api::traits::async>::events_start(Event events_a)
{
    ll::usart::CR1::Flag enabled_events;

    if (Event::character_matched == (Event::character_matched & events_a))
    {
        enabled_events |= ll::usart::CR1::cmie;
    }
    if (Event::idle == (Event::idle & events_a))
    {
        enabled_events |= ll::usart::CR1::idleie;
    }
    if (Event::transfer_complete == (Event::transfer_complete & events_a))
    {
        enabled_events |= ll::usart::CR1::tcie;
    }

    bit::flag::set(&(this->cr1), enabled_events | ll::usart::CR1::peie);
    bit::flag::set(&(this->cr3), ll::usart::CR3::eie);
}
void usart::Transceiver<api::traits::async>::events_stop()
{
    bit::flag::clear(&(this->cr1), ll::usart::CR1::idleie | ll::usart::CR1::cmie | ll::usart::CR1::tcie | ll::usart::CR1::peie);
    bit::flag::clear(&(this->cr3), ll::usart::CR3::eie);
}

__WEAK void
usart::Transceiver<api::traits::async>::handler::on_receive(std::uint32_t word_a, Error errors_a, Transceiver<api::traits::async>*)
{
}
__WEAK std::uint32_t usart::Transceiver<api::traits::async>::handler::on_transmit(Transceiver<api::traits::async>*)
{
    return no_data_to_transmit;
}
__WEAK void usart::Transceiver<api::traits::async>::handler::on_event(Event events_a, Error errors_a, Transceiver<api::traits::async>*) {}
} // namespace soc::st::arm::m0::u0::rm0503::peripherals
#endif