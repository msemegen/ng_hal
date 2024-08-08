#pragma once

/*
 *	Name: usart.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cassert>
#include <chrono>
#include <span>

// CMSIS
#include <stm32u0xx.h>

// xmcu
#include <xmcu/macros.hpp>
#include <xmcu/non_constructible.hpp>
#include <xmcu/various.hpp>

// soc
#include <soc/st/arm/IRQ_priority.hpp>
#include <soc/st/arm/api.hpp>
#include <soc/st/arm/m0/u0/rm0503/clocks/pclk.hpp>
#include <soc/st/arm/m0/u0/rm0503/clocks/sysclk.hpp>
#include <soc/st/arm/m0/u0/rm0503/oscillators/hsi16.hpp>
#include <soc/st/arm/m0/u0/rm0503/oscillators/lse.hpp>
#include <soc/st/arm/m0/u0/rm0503/peripherals/USART/base.hpp>

namespace soc::st::arm::m0::u0::rm0503::peripherals {
namespace ll {
struct usart_clock : private xmcu::non_constructible
{
    enum class Stop_mode_activity
    {
        disable,
        enable
    };

    template<usart_base::Id id_t, typename Source_t> static void enable(Stop_mode_activity stop_mode_a) = delete;
    template<usart_base::Id id_t> static void disable() = delete;

    template<usart_base::Id id_t> [[nodiscard]] static bool is_enabled() = delete;
    template<usart_base::Id id_t, typename Source_t> [[nodiscard]] static bool is_source_selected() = delete;
    template<usart_base::Id id_t> [[nodiscard]] static Stop_mode_activity get_stop_mode_activity() = delete;
};

struct usart : public usart_base
{
    using clock = usart_clock;

    struct Peripheral : private xmcu::non_copyable
    {
        volatile std::uint32_t cr1;         // control register 1
        volatile std::uint32_t cr2;         // control register 2
        volatile std::uint32_t cr3;         // control register 3
        volatile std::uint32_t brr;         // baud rate register
        volatile std::uint32_t gtpr;        // guard time and prescaler register
        volatile std::uint32_t rtor;        // receiver Time Out register
        mutable volatile std::uint32_t rqr; // request register
        volatile std::uint32_t isr;         // interrupt and status register
        mutable volatile std::uint32_t icr; // interrupt flag Clear register
        volatile std::uint32_t rdr;         // receive Data register
        volatile std::uint32_t tdr;         // transmit Data register
        volatile std::uint32_t presc;       // clock Prescaler register
    };

    template<usart::Id id_t> [[nodiscard]] constexpr static Peripheral* peripheral() = delete;
};

#if defined XMCU_USART1_PRESENT
template<> [[nodiscard]] inline constexpr usart::Peripheral* usart::peripheral<usart::_1>()
{
    return reinterpret_cast<usart::Peripheral*>(USART1_BASE);
}

template<> inline void usart_clock::enable<usart_base::_1, oscillators::hsi16>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_USART1SEL, RCC_CCIPR_USART1SEL_1);
    xmcu::bit::flag::set(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_1, oscillators::hsi16>()
{
    return false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART1SEL_0) &&
           true == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART1SEL_1);
}
template<> inline void usart_clock::enable<usart_base::_1, oscillators::lse>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_USART1SEL, RCC_CCIPR_USART1SEL_0 | RCC_CCIPR_USART1SEL_1);
    xmcu::bit::flag::set(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_1, oscillators::lse>()
{
    return xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART1SEL_0 | RCC_CCIPR_USART1SEL_1);
}
template<> inline void usart_clock::enable<usart_base::_1, clocks::pclk>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
    }

    xmcu::bit::flag::clear(&(RCC->CCIPR), RCC_CCIPR_USART1SEL);
    xmcu::bit::flag::set(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_1, clocks::pclk>()
{
    return false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART1SEL_0 | RCC_CCIPR_USART1SEL_1);
}
template<> inline void usart_clock::enable<usart_base::_1, clocks::sysclk>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_USART1SEL, RCC_CCIPR_USART1SEL_0);
    xmcu::bit::flag::set(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_1, clocks::sysclk>()
{
    return true == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART1SEL_0) &&
           false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART1SEL_1);
}
template<> inline void usart_clock::disable<usart_base::_1>()
{
    xmcu::bit::flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
    xmcu::bit::flag::clear(&(RCC->CCIPR), RCC_CCIPR_USART1SEL);
    xmcu::bit::flag::clear(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_enabled<usart_base::_1>()
{
    return xmcu::bit::flag::is(RCC->APBENR2, RCC_APBENR2_USART1EN);
}
template<> [[nodiscard]] inline usart_clock::Stop_mode_activity usart_clock::get_stop_mode_activity<usart_base::_1>()
{
    return true == xmcu::bit::flag::is(RCC->APBSMENR2, RCC_APBSMENR2_USART1SMEN) ? Stop_mode_activity::enable : Stop_mode_activity::disable;
}
#endif
#if defined XMCU_USART2_PRESENT
template<> [[nodiscard]] inline constexpr usart::Peripheral* usart::peripheral<usart::_2>()
{
    return reinterpret_cast<usart::Peripheral*>(USART2_BASE);
}

template<> inline void usart_clock::enable<usart_base::_2, oscillators::hsi16>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_USART2SEL, RCC_CCIPR_USART2SEL_1);
    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_2, oscillators::hsi16>()
{
    return false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART2SEL_0) &&
           true == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART2SEL_1);
}
template<> inline void usart_clock::enable<usart_base::_2, oscillators::lse>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_USART2SEL, RCC_CCIPR_USART2SEL_0 | RCC_CCIPR_USART2SEL_1);
    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_2, oscillators::lse>()
{
    return xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART2SEL_0 | RCC_CCIPR_USART2SEL_1);
}
template<> inline void usart_clock::enable<usart_base::_2, clocks::pclk>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
    }

    xmcu::bit::flag::clear(&(RCC->CCIPR), RCC_CCIPR_USART2SEL);
    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_2, clocks::pclk>()
{
    return false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART2SEL_0 | RCC_CCIPR_USART2SEL_1);
}
template<> inline void usart_clock::enable<usart_base::_2, clocks::sysclk>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_USART2SEL, RCC_CCIPR_USART2SEL_0);
    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_2, clocks::sysclk>()
{
    return true == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART2SEL_0) &&
           false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART2SEL_1);
}
template<> inline void usart_clock::disable<usart_base::_2>()
{
    xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
    xmcu::bit::flag::clear(&(RCC->CCIPR), RCC_CCIPR_USART2SEL);
    xmcu::bit::flag::clear(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_enabled<usart_base::_2>()
{
    return xmcu::bit::flag::is(RCC->APBENR1, RCC_APBENR1_USART2EN);
}
template<> [[nodiscard]] inline usart_clock::Stop_mode_activity usart_clock::get_stop_mode_activity<usart_base::_2>()
{
    return true == xmcu::bit::flag::is(RCC->APBSMENR1, RCC_APBSMENR1_USART2SMEN) ? Stop_mode_activity::enable : Stop_mode_activity::disable;
}
#endif
#if defined XMCU_USART3_PRESENT
template<> [[nodiscard]] inline constexpr usart::Peripheral* usart::peripheral<usart::_3>()
{
    return reinterpret_cast<usart::Peripheral*>(USART3_BASE);
}

template<> inline void usart_clock::enable<usart_base::_3, clocks::pclk>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART3SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART3SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_USART3EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_3, clocks::pclk>()
{
    return true;
}
template<> [[nodiscard]] inline constexpr bool usart_clock::is_source_selected<usart_base::_3, oscillators::hsi16>()
{
    return false;
}
template<> [[nodiscard]] inline constexpr bool usart_clock::is_source_selected<usart_base::_3, oscillators::lse>()
{
    return false;
}
template<> [[nodiscard]] inline constexpr bool usart_clock::is_source_selected<usart_base::_3, clocks::sysclk>()
{
    return false;
}
template<> inline void usart_clock::disable<usart_base::_3>()
{
    xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART3SMEN);
    xmcu::bit::flag::clear(&(RCC->APBENR1), RCC_APBENR1_USART3EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_enabled<usart_base::_3>()
{
    return xmcu::bit::flag::is(RCC->APBENR1, RCC_APBENR1_USART3EN);
}
template<> [[nodiscard]] inline usart_clock::Stop_mode_activity usart_clock::get_stop_mode_activity<usart_base::_3>()
{
    return true == xmcu::bit::flag::is(RCC->APBSMENR1, RCC_APBSMENR1_USART3SMEN) ? Stop_mode_activity::enable : Stop_mode_activity::disable;
}
#endif
#if defined XMCU_USART4_PRESENT
template<> [[nodiscard]] inline constexpr usart::Peripheral* usart::peripheral<usart::_4>()
{
    return reinterpret_cast<usart::Peripheral*>(USART4_BASE);
}

template<> inline void usart_clock::enable<usart_base::_4, clocks::pclk>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART4SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART4SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_USART4EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_4, clocks::pclk>()
{
    return true;
}
template<> [[nodiscard]] inline constexpr bool usart_clock::is_source_selected<usart_base::_4, oscillators::hsi16>()
{
    return false;
}
template<> [[nodiscard]] inline constexpr bool usart_clock::is_source_selected<usart_base::_4, oscillators::lse>()
{
    return false;
}
template<> [[nodiscard]] inline constexpr bool usart_clock::is_source_selected<usart_base::_4, clocks::sysclk>()
{
    return false;
}
template<> inline void usart_clock::disable<usart_base::_4>()
{
    xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART4SMEN);
    xmcu::bit::flag::clear(&(RCC->APBENR1), RCC_APBENR1_USART4EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_enabled<usart_base::_4>()
{
    return xmcu::bit::flag::is(RCC->APBENR1, RCC_APBENR1_USART4EN);
}
template<> [[nodiscard]] inline usart_clock::Stop_mode_activity usart_clock::get_stop_mode_activity<usart_base::_4>()
{
    return true == xmcu::bit::flag::is(RCC->APBSMENR1, RCC_APBSMENR1_USART4SMEN) ? Stop_mode_activity::enable : Stop_mode_activity::disable;
}
#endif
} // namespace ll

struct usart : public usart_base
{
    using clock = ll::usart_clock;

    class Peripheral;

    enum class Error : std::uint32_t
    {
        none,
        framing = USART_ISR_FE,
        noise = USART_ISR_NE,
        overrun = USART_ISR_ORE,
        parity = USART_ISR_PE
    };
    enum class Event : std::uint32_t
    {
        none,
        idle = USART_ISR_IDLE,
        transfer_complete = USART_ISR_TC,
        character_matched = USART_ISR_CMF
    };

    enum class Mode : std::uint32_t
    {
        tx = USART_CR1_TE,
        rx = USART_CR1_RE
    };
    enum class Stop_mode_activity : std::uint32_t
    {
        disable,
        enable = USART_CR1_UESM
    };

    enum class Fifo : std::uint32_t
    {
        disable = 0x0u,
        enable = USART_CR1_FIFOEN
    };
    enum class Oversampling : std::uint32_t
    {
        _16 = 0x0u,
        _8 = USART_CR1_OVER8,
    };
    enum class Sampling : std::uint32_t
    {
        three_sample_bit = 0,
        one_sample_bit = USART_CR3_ONEBIT,
    };
    enum class Mute : std::uint32_t
    {
        disable = 0x0u,
        wake_on_idle_line = USART_CR1_MME,
        wake_on_address = USART_CR1_MME | USART_CR1_WAKE,
    };
    enum class Auto_baudrate : std::uint64_t
    {
        _0x7f = USART_CR2_RTOEN | USART_CR2_ABRMODE_1,
        _0x55 = USART_CR2_RTOEN | USART_CR2_ABRMODE_0 | USART_CR2_ABRMODE_1
    };
    enum class Prescaler : std::uint32_t
    {
        _1 = 0x0u,
        _2 = 0x1u,
        _4 = 0x2u,
        _6 = 0x3u,
        _8 = 0x4u,
        _10 = 0x5u,
        _12 = 0x6u,
        _16 = 0x7u,
        _32 = 0x8u,
        _64 = 0x9u,
        _128 = 0xAu,
        _256 = 0xBu
    };

    struct Frame
    {
        enum class Word_length : std::uint32_t
        {
            _7_bit = USART_CR1_M1,
            _8_bit = 0x0u,
            _9_bit = USART_CR1_M0,
        };
        enum class Parity : std::uint32_t
        {
            none = 0x0u,
            even = USART_CR1_PCE,
            odd = USART_CR1_PCE | USART_CR1_PS,
        };
        enum class Stop_bits : std::uint32_t
        {
            _0_5 = USART_CR2_STOP_0,
            _1 = 0x0u,
            _1_5 = USART_CR2_STOP_0 | USART_CR2_STOP_1,
            _2 = USART_CR2_STOP_1,
        };
        enum class MSB_first : std::uint32_t
        {
            disable = 0x0u,
            enable = USART_CR2_MSBFIRST
        };
        enum class Inversion : std::uint32_t
        {
            disable = 0x0u,
            enable = USART_CR2_DATAINV
        };

        Word_length word_length;
        Parity parity;
        Stop_bits stop_bits;
        MSB_first msb_first;
        Inversion inversion;
    };

    struct Baudrate
    {
        Baudrate() {}
        Baudrate(std::uint32_t value_a)
            : v(static_cast<std::uint64_t>(value_a) << 32u)
        {
        }
        Baudrate(Auto_baudrate flag_a)
            : v(static_cast<std::uint32_t>(flag_a))
        {
        }

        operator std::uint64_t() const
        {
            return this->v;
        }

    private:
        std::uint64_t v = 0u;
    };

    struct Descriptor
    {
        Prescaler prescaler;
        Fifo fifo;
        Oversampling oversampling;
        Sampling sampling;
        Mute mute;
        Baudrate baudrate;

        Frame frame;
    };

    struct traits : private xmcu::non_constructible
    {
    private:
        enum class Kind : std::uint32_t
        {
            synchronous,
            full_duplex,
            half_duplex,
            hardware_flow_control,
        };
        enum class Hardware_flow_control
        {
            cts,
            rts
        };

        friend usart;

    public:
        struct master
        {
        };
        struct slave
        {
        };

        template<auto pin_t, gpio::Descriptor<gpio::Mode::alternate> cts_descriptor_t> struct cts
        {
            constexpr static Hardware_flow_control kind = Hardware_flow_control::cts;

            constexpr static auto pin = pin_t;
            constexpr static auto pin_descriptor = cts_descriptor_t;
        };
        template<auto pin_t, gpio::Descriptor<gpio::Mode::alternate> rts_descriptor_t> struct rts
        {
            constexpr static Hardware_flow_control kind = Hardware_flow_control::rts;

            constexpr static auto pin = pin_t;
            constexpr static auto pin_descriptor = rts_descriptor_t;
        };

        template<auto clk_pin_t, gpio::Descriptor<gpio::Mode::alternate> clk_descriptor_t, typename Type_t> struct synchronous
        {
            constexpr static Kind trait_kind = Kind::synchronous;

            constexpr static auto pin = clk_pin_t;
            constexpr static auto clk_descriptor = clk_descriptor_t;

            using Type = Type_t;
        };

        template<auto rx_pin_t,
                 gpio::Descriptor<gpio::Mode::alternate> rx_descriptor_t,
                 auto tx_pin_t,
                 gpio::Descriptor<gpio::Mode::alternate> tx_descriptor_t>
        struct full_duplex
        {
            constexpr static Kind trait_kind = Kind::full_duplex;

            constexpr static auto rx_pin = rx_pin_t;
            constexpr static auto rx_descriptor = rx_descriptor_t;
            constexpr static auto tx_pin = tx_pin_t;
            constexpr static auto tx_descriptor = tx_descriptor_t;
        };
        template<auto rxtx_pin_t, gpio::Descriptor<gpio::Mode::alternate> rxtx_descriptor_t> struct half_duplex
        {
            constexpr static Kind trait_kind = Kind::half_duplex;

            constexpr static auto rxtx_pin = rxtx_pin_t;
            constexpr static auto rxtx_descriptor = rxtx_descriptor_t;
        };

        template<typename a_t, typename b_t = const void> struct hardware_flow_control
        {
            constexpr static Kind trait_kind = Kind::hardware_flow_control;

            using a = a_t;
            using b = b_t;
        };
    };

    class Peripheral : private ll::usart::Peripheral
    {
    public:
        void set_descriptor(const Descriptor& descriptor_a);
        Descriptor get_descriptor() const
        {
            return {};
        }

        bool enable(Mode mode_a, Stop_mode_activity stop_mode_activity_a, std::chrono::milliseconds timeout_a);
        bool disable(std::chrono::milliseconds timeout_a);

        std::pair<bool, Mode> is_enabled() const;
        Id get_id() const
        {
            return static_cast<Id>(reinterpret_cast<std::uintptr_t>(this));
        }

        template<typename Type_t> Type_t* view() const = delete;
    };

    template<api::traits trait_t> class Transceiver : private non_constructible
    {
    };

    template<usart::Id id_t> [[nodiscard]] constexpr static Peripheral* peripheral() = delete;

    template<usart::Id id_t, typename transmission_mode_t, typename trait_a_t = const void, typename trait_b_t = const void>
    static void set_traits()
    {
        if constexpr (transmission_mode_t::trait_kind == traits::Kind::full_duplex)
        {
            static_assert(get_allowed_rx_pins<id_t>().is(transmission_mode_t::rx_pin), "incorrect rx pin");
            static_assert(get_allowed_tx_pins<id_t>().is(transmission_mode_t::tx_pin), "incorrect tx pin");

            detail::rx_pin<id_t, transmission_mode_t::rx_descriptor, transmission_mode_t::rx_pin>::configure();
            detail::tx_pin<id_t, transmission_mode_t::tx_descriptor, transmission_mode_t::tx_pin>::configure();
        }
        else if constexpr (transmission_mode_t::trait_kind == traits::Kind::half_duplex)
        {
            static_assert(get_allowed_tx_pins<id_t>().is(transmission_mode_t::rxtx_pin), "incorrect rx/tx pin");

            detail::tx_pin<id_t, transmission_mode_t::a_descriptor, transmission_mode_t::a_pin>::configure();
        }
        else
        {
            static_assert(false, "Unknown transmission mode (expected: usart::traits::full_duplex or usart::traits::half_duplex)");
        }

        if constexpr (false == std::is_same_v<trait_a_t, const void>)
        {
            if constexpr (transmission_mode_t::trait_kind == traits::Kind::full_duplex)
            {
                if constexpr (trait_a_t::trait_kind == traits::Kind::synchronous)
                {
                    static_assert(get_allowed_ck_pins<id_t>().is(trait_a_t::pin), "incorrect clock pin");
                    detail::clk_pin<id_t, trait_a_t::clk_descriptor, trait_a_t::pin>::configure();
                }

                if constexpr (trait_a_t::trait_kind == traits::Kind::hardware_flow_control)
                {
                    if constexpr (false == std::is_same_v<trait_b_t, const void>)
                    {
                        static_assert(trait_b_t::trait_kind != traits::Kind::synchronous,
                                      "usart::traits::hardware_flow_control is not supported with "
                                      "usart::traits::synchronous");
                    }

                    if constexpr (false == std::is_same_v<typename trait_a_t::b, const void>)
                    {
                        static_assert(trait_a_t::a::kind != trait_a_t::b::kind);

                        configure_cts_and_rts<id_t, trait_a_t>();
                    }
                    else
                    {
                        configure_cts_or_rts<id_t, trait_a_t>();
                    }
                }
            }
            else
            {
                static_assert(false,
                              "usart::traits::hardware_flow_control or usart::traits::synchronous not supported "
                              "with usart::traits::half_duplex");
            }
        }

        if constexpr (false == std::is_same_v<trait_b_t, const void>)
        {
            if constexpr (trait_a_t::trait_kind == traits::Kind::synchronous)
            {
                // possible values for trait_b_t are:
                if constexpr (trait_b_t::trait_kind == traits::Kind::hardware_flow_control)
                {
                    static_assert(trait_a_t::trait_kind != traits::Kind::synchronous,
                                  "usart::traits::hardware_flow_control is not supported with usart::traits::synchronous");

                    if constexpr (false == std::is_same_v<typename trait_b_t::b, const void>)
                    {
                        static_assert(trait_b_t::a::kind != trait_b_t::b::kind);

                        configure_cts_and_rts<id_t, trait_b_t>();
                    }
                    else
                    {
                        configure_cts_or_rts<id_t, trait_b_t>();
                    }
                }
                else
                {
                    static_assert(false, "synchronous mode already set");
                }
            }

            if constexpr (trait_a_t::trait_kind == traits::Kind::hardware_flow_control)
            {
                // possible values for trait_b_t are:
                if constexpr (trait_b_t::trait_kind == traits::Kind::synchronous)
                {
                    static_assert(get_allowed_ck_pins<id_t>().is(trait_b_t::pin), "incorrect clock pin");
                    detail::clk_pin<id_t, trait_b_t::clk_descriptor, trait_b_t::pin>::configure();
                }
                else
                {
                    static_assert(false, "hardwawe_flow_control already set");
                }
            }
        }
    }

private:
    template<usart::Id id_t, typename trait_t> void configure_cts_and_rts()
    {
        // cts configuration
        if constexpr (trait_t::a::kind == usart::traits::Hardware_flow_control::cts)
        {
            static_assert(get_allowed_cts_pins<id_t>().is(trait_t::a::pin), "incorrect cts pin");

            detail::cts_pin<id_t, trait_t::a::pin_descriptor, trait_t::a::pin>::configure();
        }
        if constexpr (trait_t::b::kind == usart::traits::Hardware_flow_control::cts)
        {
            static_assert(get_allowed_cts_pins<id_t>().is(trait_t::b::pin), "incorrect cts pin");

            detail::cts_pin<id_t, trait_t::b::pin_descriptor, trait_t::b::pin>::configure();
        }

        // rts configuration
        if constexpr (trait_t::a::kind == usart::traits::Hardware_flow_control::rts)
        {
            static_assert(get_allowed_rts_pins<id_t>().is(trait_t::a::pin), "incorrect rts pin");

            detail::rts_pin<id_t, trait_t::a::pin_descriptor, trait_t::a::pin>::configure();
        }
        if constexpr (trait_t::b::kind == usart::traits::Hardware_flow_control::rts)
        {
            static_assert(get_allowed_rts_pins<id_t>().is(trait_t::b::pin), "incorrect rts pin");

            detail::rts_pin<id_t, trait_t::b::pin_descriptor, trait_t::b::pin>::configure();
        }
    }
    template<usart::Id id_t, typename trait_t> void configure_cts_or_rts()
    {
        // cts configuration
        if constexpr (trait_t::a::kind == usart::traits::Hardware_flow_control::cts)
        {
            static_assert(get_allowed_cts_pins<id_t>().is(trait_t::a::pin), "incorrect cts pin");

            detail::cts_pin<id_t, trait_t::a::pin_descriptor, trait_t::a::pin>::configure();
        }
        // rts configuration
        else if constexpr (trait_t::a::kind == usart::traits::Hardware_flow_control::rts)
        {
            static_assert(get_allowed_rts_pins<id_t>().is(trait_t::a::pin), "incorrect rts pin");

            detail::rts_pin<id_t, trait_t::a::pin_descriptor, trait_t::a::pin>::configure();
        }
    }
};

inline constexpr usart::Error operator|(usart::Error left_a, usart::Error right_a)
{
    return static_cast<usart::Error>(static_cast<std::underlying_type<usart::Error>::type>(left_a) |
                                     static_cast<std::underlying_type<usart::Error>::type>(right_a));
}
inline constexpr usart::Error operator&(usart::Error left_a, usart::Error right_a)
{
    return static_cast<usart::Error>(static_cast<std::underlying_type<usart::Error>::type>(left_a) &
                                     static_cast<std::underlying_type<usart::Error>::type>(right_a));
}
inline constexpr usart::Error& operator|=(usart::Error& left_a, usart::Error right_a)
{
    left_a = left_a | right_a;
    return left_a;
}
inline constexpr usart::Error& operator&=(usart::Error& left_a, usart::Error right_a)
{
    left_a = left_a & right_a;
    return left_a;
}

inline constexpr usart::Event operator|(usart::Event left_a, usart::Event right_a)
{
    return static_cast<usart::Event>(static_cast<std::underlying_type<usart::Event>::type>(left_a) |
                                     static_cast<std::underlying_type<usart::Event>::type>(right_a));
}
inline constexpr usart::Event operator&(usart::Event left_a, usart::Event right_a)
{
    return static_cast<usart::Event>(static_cast<std::underlying_type<usart::Event>::type>(left_a) &
                                     static_cast<std::underlying_type<usart::Event>::type>(right_a));
}
inline constexpr usart::Event& operator|=(usart::Event& left_a, usart::Event right_a)
{
    left_a = left_a | right_a;
    return left_a;
}
inline constexpr usart::Event& operator&=(usart::Event& left_a, usart::Event right_a)
{
    left_a = left_a & right_a;
    return left_a;
}

inline constexpr usart::Mode operator|(usart::Mode left_a, usart::Mode right_a)
{
    return static_cast<usart::Mode>(static_cast<std::underlying_type<usart::Mode>::type>(left_a) |
                                    static_cast<std::underlying_type<usart::Mode>::type>(right_a));
}
inline constexpr usart::Mode operator&(usart::Mode left_a, usart::Mode right_a)
{
    return static_cast<usart::Mode>(static_cast<std::underlying_type<usart::Mode>::type>(left_a) &
                                    static_cast<std::underlying_type<usart::Mode>::type>(right_a));
}

inline constexpr usart::Mute operator|(usart::Mute mode_a, std::uint8_t address_a)
{
    if (mode_a == usart::Mute::wake_on_address)
    {
        return static_cast<usart::Mute>(static_cast<std::uint32_t>(mode_a) | address_a);
    }
    else
    {
        assert(mode_a == usart::Mute::wake_on_address);
        return mode_a;
    }
}

#if defined XMCU_USART1_PRESENT
template<> [[nodiscard]] inline constexpr usart::Peripheral* usart::peripheral<usart::_1>()
{
    return reinterpret_cast<usart::Peripheral*>(USART1_BASE);
}
#endif
#if defined XMCU_USART2_PRESENT
template<> [[nodiscard]] inline constexpr usart::Peripheral* usart::peripheral<usart::_2>()
{
    return reinterpret_cast<usart::Peripheral*>(USART2_BASE);
}
#endif
#if defined XMCU_USART3_PRESENT
template<> [[nodiscard]] inline constexpr usart::Peripheral* usart::peripheral<usart::_3>()
{
    return reinterpret_cast<usart::Peripheral*>(USART3_BASE);
}
#endif
#if defined XMCU_USART4_PRESENT
template<> [[nodiscard]] inline constexpr usart::Peripheral* usart::peripheral<usart::_4>()
{
    return reinterpret_cast<usart::Peripheral*>(USART4_BASE);
}
#endif

template<> class usart::Transceiver<api::traits::sync> : private ll::usart::Peripheral
{
public:
    std::pair<std::size_t, usart::Error> receive(std::span<std::uint8_t> out_a) const
    {
        return this->receive(out_a);
    }
    std::pair<std::size_t, usart::Error> receive(std::span<char> out_a) const
    {
        return this->receive(out_a);
    }
    std::pair<std::size_t, usart::Error> receive(std::span<std::uint16_t> out_a) const
    {
        return this->receive(out_a);
    }
    std::pair<std::size_t, usart::Error> receive(std::span<std::uint8_t> out_a, std::chrono::milliseconds timeout_a) const
    {
        return this->receive(out_a, timeout_a);
    }
    std::pair<std::size_t, usart::Error> receive(std::span<char> out_a, std::chrono::milliseconds timeout_a) const
    {
        return this->receive(out_a, timeout_a);
    }
    std::pair<std::size_t, usart::Error> receive(std::span<std::uint16_t> out_a, std::chrono::milliseconds timeout_a) const
    {
        return this->receive(out_a, timeout_a);
    }

    std::size_t transmit(std::span<const std::uint8_t> data_a)
    {
        return this->trasmit(data_a);
    }
    std::size_t transmit(std::string_view data_a)
    {
        return this->trasmit(std::span { data_a.data(), data_a.length() });
    }
    std::size_t transmit(std::span<const char> data_a)
    {
        return this->trasmit(data_a);
    }
    std::size_t transmit(std::span<const std::uint16_t> data_a)
    {
        return this->trasmit(data_a);
    }
    std::size_t transmit(std::span<const std::uint8_t> data_a, std::chrono::milliseconds timeout_a)
    {
        return this->trasmit(data_a, timeout_a);
    }
    std::size_t transmit(std::string_view data_a, std::chrono::milliseconds timeout_a)
    {
        return this->trasmit(std::span { data_a.data(), data_a.length() }, timeout_a);
    }
    std::size_t transmit(std::span<const char> data_a, std::chrono::milliseconds timeout_a)
    {
        return this->trasmit(data_a, timeout_a);
    }
    std::size_t transmit(std::span<const std::uint16_t> data_a, std::chrono::milliseconds timeout_a)
    {
        return this->trasmit(data_a, timeout_a);
    }

private:
    template<typename Word_t> std::size_t trasmit(std::span<const Word_t> data_a)
    {
        assert(true == xmcu::bit::flag::is(this->isr, USART_ISR_TEACK));

        std::size_t sent = 0;

        while (sent < data_a.size())
        {
            if (true == xmcu::bit::flag::is(this->isr, USART_ISR_TXE_TXFNF))
            {
                this->tdr = data_a[sent];
                sent++;
            }
        }

        xmcu::bit::wait_for::all_set(this->isr, USART_ISR_TC);
        xmcu::bit::flag::set(&(this->icr), USART_ICR_TCCF);

        return sent;
    }
    template<typename Word_t> std::size_t trasmit(std::span<const Word_t> data_a, std::chrono::milliseconds timeout_a)
    {
        assert(true == xmcu::bit::flag::is(this->isr, USART_ISR_TEACK));

        std::size_t sent = 0;
        const std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + timeout_a;

        while (sent < data_a.size() && std::chrono::steady_clock::now() <= timeout)
        {
            if (true == xmcu::bit::flag::is(this->isr, USART_ISR_TXE_TXFNF))
            {
                this->tdr = data_a[sent];
                sent++;
            }
        }

        xmcu::bit::wait_for::all_set(this->isr, USART_ISR_TC);
        xmcu::bit::flag::set(&(this->icr), USART_ICR_TCCF);

        return sent;
    }

    template<typename Word_t> std::pair<std::size_t, usart::Error> receive(std::span<Word_t> out_a) const
    {
        assert(true == xmcu::bit::flag::is(this->isr, USART_ISR_REACK));

        std::size_t received = 0;
        while (false == xmcu::bit::flag::is(this->isr, USART_ISR_IDLE) && Error::none == this->get_rx_error())
        {
            if (true == xmcu::bit::flag::is(this->isr, USART_ISR_RXNE_RXFNE))
            {
                if (true == xmcu::bit::flag::is(this->isr, USART_ISR_CMF) &&
                    true == xmcu::bit::flag::is(this->cr1, USART_CR1_MME | USART_CR1_WAKE))
                {
                    xmcu::bit::flag::set(&(this->icr), USART_ICR_CMCF);
                }

                if (received < out_a.size())
                {
                    out_a[received++] = static_cast<Word_t>(this->rdr);
                }
                else
                {
                    xmcu::bit::flag::set(&(this->rqr), USART_RQR_RXFRQ);
                }
            }
        }

        xmcu::bit::flag::set(&(this->icr), USART_ICR_IDLECF);

        const Error err = this->get_rx_error();

        if (Error::none != err)
        {
            xmcu::bit::flag::set(&(this->icr), USART_ICR_FECF | USART_ICR_NECF | USART_ICR_ORECF | USART_ICR_PECF);

            return { received, err };
        }

        return { received, Error::none };
    }
    template<typename Word_t>
    std::pair<std::size_t, usart::Error> receive(std::span<Word_t> out_a, std::chrono::milliseconds timeout_a) const
    {
        assert(true == xmcu::bit::flag::is(this->isr, USART_ISR_REACK));

        std::size_t received = 0;
        const std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + timeout_a;

        while (false == xmcu::bit::flag::is(this->isr, USART_ISR_IDLE) && Error::none == this->get_rx_error() &&
               std::chrono::steady_clock::now() <= timeout)
        {
            if (true == xmcu::bit::flag::is(this->isr, USART_ISR_RXNE_RXFNE))
            {
                if (true == xmcu::bit::flag::is(this->isr, USART_ISR_CMF) &&
                    true == xmcu::bit::flag::is(this->cr1, USART_CR1_MME | USART_CR1_WAKE))
                {
                    xmcu::bit::flag::set(&(this->icr), USART_ICR_CMCF);
                }

                if (received < out_a.size())
                {
                    out_a[received++] = static_cast<Word_t>(this->rdr);
                }
                else
                {
                    xmcu::bit::flag::set(&(this->rqr), USART_RQR_RXFRQ);
                }
            }
        }

        xmcu::bit::flag::set(&(this->icr), USART_ICR_IDLECF);

        const Error err = this->get_rx_error();

        if (Error::none != err)
        {
            xmcu::bit::flag::set(&(this->icr), USART_ICR_FECF | USART_ICR_NECF | USART_ICR_ORECF | USART_ICR_PECF);

            return { received, err };
        }

        return { received, Error::none };
    }

    Error get_rx_error() const
    {
        return static_cast<Error>(xmcu::bit::flag::get(this->isr, USART_ISR_FE | USART_ISR_NE | USART_ISR_ORE | USART_ISR_PE));
    }
};
template<> class usart::Transceiver<api::traits::async> : private ll::usart::Peripheral
{
public:
#if 1 == XMCU_ISR_CONTEXT
    void enable(const IRQ_priority& priority_a, void* p_context_a);
#endif

#if 0 == XMCU_ISR_CONTEXT
    void enable(const IRQ_priority& priority_a);
#endif
    void disable();

    void receive_start();
    void receive_stop();

    void transmit_start();
    void transmit_stop();

    void events_start(Event events_a);
    void events_stop();

    struct handler : private xmcu::non_constructible
    {
        static void on_receive(std::uint32_t word_a, Error errors_a, usart::Transceiver<api::traits::async>* p_this);
        static std::uint32_t on_transmit(usart::Transceiver<api::traits::async>* p_this);

        static void on_event(Event events_a, Error errors_a, usart::Transceiver<api::traits::async>* p_this);
    };

private:
    friend void usart_isr_handler(usart::Transceiver<api::traits::async>* p_handler_a);

    constexpr static std::uint32_t no_data_to_transmit = 0x200u;
};

template<> inline usart::Transceiver<api::traits::sync>* usart::Peripheral::view<usart::Transceiver<api::traits::sync>>() const
{
    const std::uintptr_t base_address = reinterpret_cast<std::uintptr_t>(this);
    return reinterpret_cast<Transceiver<api::traits::sync>*>(base_address);
}

template<> inline usart::Transceiver<api::traits::async>* usart::Peripheral::view<usart::Transceiver<api::traits::async>>() const
{
    const std::uint32_t base_address = reinterpret_cast<std::uint32_t>(this);
    return reinterpret_cast<Transceiver<api::traits::async>*>(base_address);
}
} // namespace soc::st::arm::m0::u0::rm0503::peripherals