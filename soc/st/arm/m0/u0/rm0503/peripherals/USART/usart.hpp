#pragma once

/*
 *	Name: usart.hpp
 *
 *   Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *   Licensed under the MIT license. See LICENSE file in the project root for details.
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
#include <xmcu/wait_for.hpp>

// soc
#include <soc/st/arm/api.hpp>
#include <soc/st/arm/m0/u0/rm0503/clocks/pclk.hpp>
#include <soc/st/arm/m0/u0/rm0503/clocks/sysclk.hpp>
#include <soc/st/arm/m0/u0/rm0503/oscillators/hsi16.hpp>
#include <soc/st/arm/m0/u0/rm0503/oscillators/lse.hpp>
#include <soc/st/arm/m0/u0/rm0503/peripherals/USART/base.hpp>
#include <soc/st/arm/m0/u0/rm0503/peripherals/USART/usart.hpp>

namespace soc::st::arm::m0::u0::rm0503::peripherals {
namespace ll {
struct usart_clock : private xmcu::non_constructible
{
    enum class Active_in_low_power
    {
        disable,
        enable
    };

    template<typename id_t, typename Source_t> static void enable(Active_in_low_power lp_a) = delete;
    template<typename id_t> static void disable() = delete;

    template<typename id_t> static bool is_enabled() = delete;
};

struct usart : public usart_base
{
    using clock = usart_clock;

    struct Port : private xmcu::Non_copyable
    {
        volatile std::uint32_t cr1;
        volatile std::uint32_t cr2;
        volatile std::uint32_t cr3;
        volatile std::uint32_t brr;  /*!< USART Baud rate register,                 Address offset: 0x0C */
        volatile std::uint32_t gtpr; /*!< USART Guard time and prescaler register,  Address offset: 0x10 */
        volatile std::uint32_t rtor; /*!< USART Receiver Time Out register,         Address offset: 0x14 */
        mutable volatile std::uint32_t rqr;
        volatile std::uint32_t isr;
        mutable volatile std::uint32_t icr;
        volatile std::uint32_t rdr;   /*!< USART Receive Data register,              Address offset: 0x24 */
        volatile std::uint32_t tdr;   /*!< USART Transmit Data register,             Address offset: 0x28 */
        volatile std::uint32_t presc; /*!< USART clock Prescaler register,           Address offset: 0x2C */
    };
};

#if defined XMCU_USART1_PRESENT
template<> inline void usart_clock::enable<usart_base::_1, oscillators::hsi16>(Active_in_low_power lp_a)
{
    switch (lp_a)
    {
        case Active_in_low_power::disable:
            xmcu::bit_flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
        case Active_in_low_power::enable:
            xmcu::bit_flag::set(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
    }

    xmcu::bit_flag::set(&(RCC->CCIPR), RCC_CCIPR_USART1SEL, RCC_CCIPR_USART1SEL_1);
    xmcu::bit_flag::set(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
template<> inline void usart_clock::enable<usart_base::_1, oscillators::lse>(Active_in_low_power lp_a)
{
    switch (lp_a)
    {
        case Active_in_low_power::disable:
            xmcu::bit_flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
        case Active_in_low_power::enable:
            xmcu::bit_flag::set(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
    }

    xmcu::bit_flag::set(&(RCC->CCIPR), RCC_CCIPR_USART1SEL, RCC_CCIPR_USART1SEL_0 | RCC_CCIPR_USART1SEL_1);
    xmcu::bit_flag::set(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
template<> inline void usart_clock::enable<usart_base::_1, clocks::pclk>(Active_in_low_power lp_a)
{
    switch (lp_a)
    {
        case Active_in_low_power::disable:
            xmcu::bit_flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
        case Active_in_low_power::enable:
            xmcu::bit_flag::set(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
    }

    xmcu::bit_flag::clear(&(RCC->CCIPR), RCC_CCIPR_USART1SEL);
    xmcu::bit_flag::set(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
template<> inline void usart_clock::enable<usart_base::_1, clocks::sysclk>(Active_in_low_power lp_a)
{
    switch (lp_a)
    {
        case Active_in_low_power::disable:
            xmcu::bit_flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
        case Active_in_low_power::enable:
            xmcu::bit_flag::set(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
    }

    xmcu::bit_flag::set(&(RCC->CCIPR), RCC_CCIPR_USART1SEL, RCC_CCIPR_USART1SEL_0);
    xmcu::bit_flag::set(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
template<> inline void usart_clock::disable<usart_base::_1>()
{
    xmcu::bit_flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
    xmcu::bit_flag::clear(&(RCC->CCIPR), RCC_CCIPR_USART1SEL);
    xmcu::bit_flag::clear(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
#endif
#if defined XMCU_USART2_PRESENT
template<> inline void usart_clock::enable<usart_base::_2, oscillators::hsi16>(Active_in_low_power lp_a)
{
    switch (lp_a)
    {
        case Active_in_low_power::disable:
            xmcu::bit_flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
        case Active_in_low_power::enable:
            xmcu::bit_flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
    }

    xmcu::bit_flag::set(&(RCC->CCIPR), RCC_CCIPR_USART2SEL, RCC_CCIPR_USART2SEL_1);
    xmcu::bit_flag::set(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
template<> inline void usart_clock::enable<usart_base::_2, oscillators::lse>(Active_in_low_power lp_a)
{
    switch (lp_a)
    {
        case Active_in_low_power::disable:
            xmcu::bit_flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
        case Active_in_low_power::enable:
            xmcu::bit_flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
    }

    xmcu::bit_flag::set(&(RCC->CCIPR), RCC_CCIPR_USART2SEL, RCC_CCIPR_USART2SEL_0 | RCC_CCIPR_USART2SEL_1);
    xmcu::bit_flag::set(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
template<> inline void usart_clock::enable<usart_base::_2, clocks::pclk>(Active_in_low_power lp_a)
{
    switch (lp_a)
    {
        case Active_in_low_power::disable:
            xmcu::bit_flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
        case Active_in_low_power::enable:
            xmcu::bit_flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
    }

    xmcu::bit_flag::clear(&(RCC->CCIPR), RCC_CCIPR_USART2SEL);
    xmcu::bit_flag::set(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
template<> inline void usart_clock::enable<usart_base::_2, clocks::sysclk>(Active_in_low_power lp_a)
{
    switch (lp_a)
    {
        case Active_in_low_power::disable:
            xmcu::bit_flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
        case Active_in_low_power::enable:
            xmcu::bit_flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
    }

    xmcu::bit_flag::set(&(RCC->CCIPR), RCC_CCIPR_USART2SEL, RCC_CCIPR_USART2SEL_0);
    xmcu::bit_flag::set(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
template<> inline void usart_clock::disable<usart_base::_2>()
{
    xmcu::bit_flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
    xmcu::bit_flag::clear(&(RCC->CCIPR), RCC_CCIPR_USART2SEL);
    xmcu::bit_flag::clear(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
#endif
#if defined XMCU_USART3_PRESENT
template<> inline void usart_clock::enable<usart_base::_3, clocks::pclk>(Active_in_low_power lp_a)
{
    switch (lp_a)
    {
        case Active_in_low_power::disable:
            xmcu::bit_flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART3SMEN);
            break;
        case Active_in_low_power::enable:
            xmcu::bit_flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART3SMEN);
            break;
    }

    xmcu::bit_flag::set(&(RCC->APBENR1), RCC_APBENR1_USART3EN);
}
template<> inline void usart_clock::disable<usart_base::_3>()
{
    xmcu::bit_flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART3SMEN);
    xmcu::bit_flag::clear(&(RCC->APBENR1), RCC_APBENR1_USART3EN);
}
#endif
#if defined XMCU_USART4_PRESENT
template<> inline void usart_clock::enable<usart_base::_4, clocks::pclk>(Active_in_low_power lp_a)
{
    switch (lp_a)
    {
        case Active_in_low_power::disable:
            xmcu::bit_flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART4SMEN);
            break;
        case Active_in_low_power::enable:
            xmcu::bit_flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART4SMEN);
            break;
    }

    xmcu::bit_flag::set(&(RCC->APBENR1), RCC_APBENR1_USART4EN);
}
template<> inline void usart_clock::disable<usart_base::_4>()
{
    xmcu::bit_flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART4SMEN);
    xmcu::bit_flag::clear(&(RCC->APBENR1), RCC_APBENR1_USART4EN);
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
        framing,
        noise,
        overrun,
        parity
    };
    enum class Mode : std::uint32_t
    {
        tx = USART_CR1_TE,
        rx = USART_CR1_RE
    };
    struct Descriptor
    {
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
            none = 0x0u,
            wake_on_idle_line = USART_CR1_MME,
            wake_on_address = USART_CR1_MME | USART_CR1_WAKE,
        };
        enum class Auto_baudrate : std::uint64_t
        {
            disable = 0x0u,
            _0x7f = USART_CR2_RTOEN | USART_CR2_ABRMODE_1,
            _0x55 = USART_CR2_RTOEN | USART_CR2_ABRMODE_0 | USART_CR2_ABRMODE_1
        };

        struct Clock
        {
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

            std::uint32_t clk_freq_Hz = 0x0u;
            Prescaler prescaler;
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

        Fifo fifo;
        Oversampling oversampling;
        Sampling sampling;
        Mute mute;
        Auto_baudrate auto_baudrate;

        Clock clock;
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

    class Peripheral : private ll::usart::Port
    {
    public:
        void set_descriptor(const Descriptor& descriptor_a);
        Descriptor get_descriptor() const
        {
            return {};
        }

        bool enable(Mode mode_a, std::chrono::milliseconds timeout_a);
        bool disable(std::chrono::milliseconds timeout_a);

        std::pair<bool, Mode> is_enabled() const;

        template<typename Type_t> Type_t* get_view() const = delete;
    };

    template<api::traits trait_t> class Transceiver : private non_constructible
    {
    };

    template<typename id_t> [[nodiscard]] constexpr static Peripheral* create() = delete;

    template<typename id_t, typename transmission_mode_t, typename trait_a_t = const void, typename trait_b_t = const void>
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
    template<typename id_t, typename trait_t> void configure_cts_and_rts()
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
    template<typename id_t, typename trait_t> void configure_cts_or_rts()
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

inline constexpr usart::Error& operator|=(usart::Error& left_a, usart::Error right_a)
{
    left_a = left_a | right_a;
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

inline constexpr usart::Descriptor::Mute operator|(usart::Descriptor::Mute mode_a, std::uint8_t address_a)
{
    if (mode_a == usart::Descriptor::Mute::wake_on_address)
    {
        return static_cast<usart::Descriptor::Mute>(static_cast<std::uint32_t>(mode_a) | address_a);
    }
    else
    {
        assert(mode_a == usart::Descriptor::Mute::wake_on_address);
        return mode_a;
    }
}

inline constexpr usart::Descriptor::Auto_baudrate operator|(usart::Descriptor::Auto_baudrate mode_a, std::uint32_t baudrate_a)
{
    if (mode_a == usart::Descriptor::Auto_baudrate::disable)
    {
        return static_cast<usart::Descriptor::Auto_baudrate>(static_cast<std::uint32_t>(mode_a) |
                                                             (static_cast<std::uint64_t>(baudrate_a) << 32u));
    }
    else
    {
        assert(mode_a == usart::Descriptor::Auto_baudrate::disable);
        return mode_a;
    }
}

inline constexpr usart::Descriptor::Auto_baudrate operator&(usart::Descriptor::Auto_baudrate left_a,
                                                            usart::Descriptor::Auto_baudrate right_a)
{
    return static_cast<usart::Descriptor::Auto_baudrate>(
        (static_cast<std::underlying_type_t<usart::Descriptor::Auto_baudrate>>(left_a) & 0xFFFFFFFF) &
        (static_cast<std::underlying_type_t<usart::Descriptor::Auto_baudrate>>(right_a) & 0xFFFFFFFF));
}

#if defined XMCU_USART1_PRESENT
template<> [[nodiscard]] inline constexpr usart::Peripheral* usart::create<usart::_1>()
{
    return reinterpret_cast<usart::Peripheral*>(USART1_BASE);
}
#endif
#if defined XMCU_USART2_PRESENT
template<> [[nodiscard]] inline constexpr usart::Peripheral* usart::create<usart::_2>()
{
    return reinterpret_cast<usart::Peripheral*>(USART2_BASE);
}
#endif
#if defined XMCU_USART3_PRESENT
template<> [[nodiscard]] inline constexpr usart::Peripheral* usart::create<usart::_3>()
{
    return reinterpret_cast<usart::Peripheral*>(USART3_BASE);
}
#endif
#if defined XMCU_USART4_PRESENT
template<> [[nodiscard]] inline constexpr usart::Peripheral* usart::create<usart::_4>()
{
    return reinterpret_cast<usart::Peripheral*>(USART4_BASE);
}
#endif

template<> class usart::Transceiver<api::traits::sync> : private ll::usart::Port
{
public:
    std::pair<std::size_t, usart::Error> read(std::span<std::uint8_t> out_a) const
    {
        return this->receive(out_a);
    }
    std::pair<std::size_t, usart::Error> read(std::span<char> out_a) const
    {
        return this->receive(out_a);
    }
    std::pair<std::size_t, usart::Error> read(std::span<std::uint16_t> out_a) const
    {
        return this->receive(out_a);
    }
    std::pair<std::size_t, usart::Error> read(std::span<std::uint8_t> out_a, std::chrono::milliseconds timeout_a) const
    {
        return this->receive(out_a, timeout_a);
    }
    std::pair<std::size_t, usart::Error> read(std::span<char> out_a, std::chrono::milliseconds timeout_a) const
    {
        return this->receive(out_a, timeout_a);
    }
    std::pair<std::size_t, usart::Error> read(std::span<std::uint16_t> out_a, std::chrono::milliseconds timeout_a) const
    {
        return this->receive(out_a, timeout_a);
    }

    std::size_t write(std::span<const std::uint8_t> data_a)
    {
        return this->trasmit(data_a);
    }
    std::size_t write(std::string_view data_a)
    {
        return this->trasmit(std::span { data_a.data(), data_a.length() });
    }
    std::size_t write(std::span<const char> data_a)
    {
        return this->trasmit(data_a);
    }
    std::size_t write(std::span<const std::uint16_t> data_a)
    {
        return this->trasmit(data_a);
    }
    std::size_t write(std::span<const std::uint8_t> data_a, std::chrono::milliseconds timeout_a)
    {
        return this->trasmit(data_a, timeout_a);
    }
    std::size_t write(std::string_view data_a, std::chrono::milliseconds timeout_a)
    {
        return this->trasmit(std::span { data_a.data(), data_a.length() }, timeout_a);
    }
    std::size_t write(std::span<const char> data_a, std::chrono::milliseconds timeout_a)
    {
        return this->trasmit(data_a, timeout_a);
    }
    std::size_t write(std::span<const std::uint16_t> data_a, std::chrono::milliseconds timeout_a)
    {
        return this->trasmit(data_a, timeout_a);
    }

private:
    template<typename Word_t> std::size_t trasmit(std::span<const Word_t> data_a)
    {
        assert(true == xmcu::bit_flag::is(this->isr, USART_ISR_TEACK));

        std::size_t sent = 0;

        while (sent < data_a.size())
        {
            if (true == xmcu::bit_flag::is(this->isr, USART_ISR_TXE_TXFNF))
            {
                this->tdr = data_a[sent];
                sent++;
            }
        }

        xmcu::wait_for::all_bits_are_set(this->isr, USART_ISR_TC);
        xmcu::bit_flag::set(&(this->icr), USART_ICR_TCCF);

        return sent;
    }
    template<typename Word_t> std::size_t trasmit(std::span<const Word_t> data_a, std::chrono::milliseconds timeout_a)
    {
        assert(true == xmcu::bit_flag::is(this->isr, USART_ISR_TEACK));

        std::size_t sent = 0;
        const std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + timeout_a;

        while (sent < data_a.size() && std::chrono::steady_clock::now() <= timeout)
        {
            if (true == xmcu::bit_flag::is(this->isr, USART_ISR_TXE_TXFNF))
            {
                this->tdr = data_a[sent];
                sent++;
            }
        }

        xmcu::wait_for::all_bits_are_set(this->isr, USART_ISR_TC);
        xmcu::bit_flag::set(&(this->icr), USART_ICR_TCCF);

        return sent;
    }

    template<typename Word_t> std::pair<std::size_t, usart::Error> receive(std::span<Word_t> out_a) const
    {
        assert(true == xmcu::bit_flag::is(this->isr, USART_ISR_REACK));

        std::size_t received = 0;
        while (false == xmcu::bit_flag::is(this->isr, USART_ISR_IDLE) && false == this->is_rx_error())
        {
            if (true == xmcu::bit_flag::is(this->isr, USART_ISR_RXNE_RXFNE))
            {
                if (true == xmcu::bit_flag::is(this->isr, USART_ISR_CMF) && true == xmcu::bit_flag::is(this->cr1, USART_CR1_MME | USART_CR1_WAKE))
                {
                    xmcu::bit_flag::set(&(this->icr), USART_ICR_CMCF);
                }

                if (received < out_a.size())
                {
                    out_a[received++] = static_cast<Word_t>(this->rdr);
                }
                else
                {
                    xmcu::bit_flag::set(&(this->rqr), USART_RQR_RXFRQ);
                }
            }
        }

        xmcu::bit_flag::set(&(this->icr), USART_ICR_IDLECF);

        if (true == this->is_rx_error())
        {
            const Error errors = this->get_rx_error();
            xmcu::bit_flag::set(&(this->icr), USART_ICR_FECF | USART_ICR_NECF | USART_ICR_ORECF | USART_ICR_PECF);

            return { received, errors };
        }

        return { received, Error::none };
    }
    template<typename Word_t>
    std::pair<std::size_t, usart::Error> receive(std::span<Word_t> out_a, std::chrono::milliseconds timeout_a) const
    {
        assert(true == xmcu::bit_flag::is(this->isr, USART_ISR_REACK));

        std::size_t received = 0;
        const std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + timeout_a;

        while (false == xmcu::bit_flag::is(this->isr, USART_ISR_IDLE) && false == this->is_rx_error() &&
               std::chrono::steady_clock::now() <= timeout)
        {
            if (true == xmcu::bit_flag::is(this->isr, USART_ISR_RXNE_RXFNE))
            {
                if (true == xmcu::bit_flag::is(this->isr, USART_ISR_CMF) &&
                    true == xmcu::bit_flag::is(this->cr1, USART_CR1_MME | USART_CR1_WAKE))
                {
                    xmcu::bit_flag::set(&(this->icr), USART_ICR_CMCF);
                }

                if (received < out_a.size())
                {
                    out_a[received++] = static_cast<Word_t>(this->rdr);
                }
                else
                {
                    xmcu::bit_flag::set(&(this->rqr), USART_RQR_RXFRQ);
                }
            }
        }

        xmcu::bit_flag::set(&(this->icr), USART_ICR_IDLECF);

        if (true == this->is_rx_error())
        {
            const Error errors = this->get_rx_error();
            xmcu::bit_flag::set(&(this->icr), USART_ICR_FECF | USART_ICR_NECF | USART_ICR_ORECF | USART_ICR_PECF);

            return { received, errors };
        }

        return { received, Error::none };
    }

    bool is_rx_error() const
    {
        return xmcu::bit::is_any(this->icr, USART_ICR_FECF | USART_ICR_NECF | USART_ICR_ORECF | USART_ICR_PECF);
    }

    Error get_rx_error() const
    {
        Error error = Error::none;

        if (true == xmcu::bit_flag::is(this->isr, USART_ISR_FE))
        {
            error |= Error::framing;
        }
        if (true == xmcu::bit_flag::is(this->isr, USART_ISR_NE))
        {
            error |= Error::noise;
        }
        if (true == xmcu::bit_flag::is(this->isr, USART_ISR_ORE))
        {
            error |= Error::overrun;
        }
        if (true == xmcu::bit_flag::is(this->isr, USART_ISR_PE))
        {
            error |= Error::parity;
        }

        return error;
    }
};
template<> class usart::Transceiver<api::traits::async> : private ll::usart::Port
{
public:
    void start();
    void stop();
};

template<> inline usart::Transceiver<api::traits::sync>* usart::Peripheral::get_view<usart::Transceiver<api::traits::sync>>() const
{
    const std::uintptr_t base_address = reinterpret_cast<std::uintptr_t>(this);
    return reinterpret_cast<Transceiver<api::traits::sync>*>(base_address);
}

template<> inline usart::Transceiver<api::traits::async>* usart::Peripheral::get_view<usart::Transceiver<api::traits::async>>() const
{
    const std::uint32_t base_address = reinterpret_cast<std::uint32_t>(this);
    return reinterpret_cast<Transceiver<api::traits::async>*>(base_address);
}
} // namespace soc::st::arm::m0::u0::rm0503::peripherals