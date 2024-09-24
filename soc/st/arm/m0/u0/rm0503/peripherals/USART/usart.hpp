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
#include <soc/st/arm/m0/u0/rm0503/peripherals/USART/usart_ll.hpp>

namespace soc::st::arm::m0::u0::rm0503::peripherals {
struct usart : public usart_base
{
    using clock = ll::usart_clock;

    class Peripheral;

    enum class Error : std::uint32_t
    {
        none,
        framing = static_cast<std::uint32_t>(ll::usart::ISR::fe),
        noise = static_cast<std::uint32_t>(ll::usart::ISR::ne),
        overrun = static_cast<std::uint32_t>(ll::usart::ISR::ore),
        parity = static_cast<std::uint32_t>(ll::usart::ISR::pe)
    };
    enum class Event : std::uint32_t
    {
        none,
        idle = static_cast<std::uint32_t>(ll::usart::ISR::idle),
        transfer_complete = static_cast<std::uint32_t>(ll::usart::ISR::tc),
        character_matched = static_cast<std::uint32_t>(ll::usart::ISR::cmf)
    };

    enum class Mode : std::uint32_t
    {
        tx = static_cast<std::uint32_t>(ll::usart::CR1::te),
        rx = static_cast<std::uint32_t>(ll::usart::CR1::re)
    };
    enum class Stop_mode_activity : std::uint32_t
    {
        disable,
        enable = static_cast<std::uint32_t>(ll::usart::CR1::uesm)
    };

    enum class Fifo : std::uint32_t
    {
        disable = 0x0u,
        enable = static_cast<std::uint32_t>(ll::usart::CR1::fifoen)
    };
    enum class Oversampling : std::uint32_t
    {
        _16 = 0x0u,
        _8 = static_cast<std::uint32_t>(ll::usart::CR1::over8),
    };
    enum class Sampling : std::uint32_t
    {
        three_sample_bit = 0,
        one_sample_bit = static_cast<std::uint32_t>(ll::usart::CR3::onebit),
    };
    enum class Mute : std::uint32_t
    {
        disable = 0x0u,
        wake_on_idle_line = static_cast<std::uint32_t>(ll::usart::CR1::mme),
        wake_on_address = static_cast<std::uint32_t>(ll::usart::CR1::mme | ll::usart::CR1::wake),
    };
    enum class Prescaler : std::uint32_t
    {
        _1 = static_cast<std::uint32_t>(ll::usart::PRESC::value::_1 << ll::usart::PRESC::shift::presc),
        _2 = static_cast<std::uint32_t>(ll::usart::PRESC::value::_2 << ll::usart::PRESC::shift::presc),
        _4 = static_cast<std::uint32_t>(ll::usart::PRESC::value::_4 << ll::usart::PRESC::shift::presc),
        _6 = static_cast<std::uint32_t>(ll::usart::PRESC::value::_6 << ll::usart::PRESC::shift::presc),
        _8 = static_cast<std::uint32_t>(ll::usart::PRESC::value::_8 << ll::usart::PRESC::shift::presc),
        _10 = static_cast<std::uint32_t>(ll::usart::PRESC::value::_10 << ll::usart::PRESC::shift::presc),
        _12 = static_cast<std::uint32_t>(ll::usart::PRESC::value::_12 << ll::usart::PRESC::shift::presc),
        _16 = static_cast<std::uint32_t>(ll::usart::PRESC::value::_16 << ll::usart::PRESC::shift::presc),
        _32 = static_cast<std::uint32_t>(ll::usart::PRESC::value::_32 << ll::usart::PRESC::shift::presc),
        _64 = static_cast<std::uint32_t>(ll::usart::PRESC::value::_64 << ll::usart::PRESC::shift::presc),
        _128 = static_cast<std::uint32_t>(ll::usart::PRESC::value::_128 << ll::usart::PRESC::shift::presc),
        _256 = static_cast<std::uint32_t>(ll::usart::PRESC::value::_256 << ll::usart::PRESC::shift::presc)
    };

    struct Frame
    {
        enum class Word_length : std::uint32_t
        {
            _7_bit = static_cast<std::uint32_t>(ll::usart::CR1::m1),
            _8_bit = 0x0u,
            _9_bit = static_cast<std::uint32_t>(ll::usart::CR1::m0),
        };
        enum class Parity : std::uint32_t
        {
            none = 0x0u,
            even = static_cast<std::uint32_t>(ll::usart::CR1::pce),
            odd = static_cast<std::uint32_t>(ll::usart::CR1::pce | ll::usart::CR1::ps),
        };
        enum class Stop_bits : std::uint32_t
        {
            _0_5 = static_cast<std::uint32_t>(ll::usart::CR2::value::stop_0_5_bit << ll::usart::CR2::shift::stop),
            _1 = static_cast<std::uint32_t>(ll::usart::CR2::value::stop_1_bit << ll::usart::CR2::shift::stop),
            _1_5 = static_cast<std::uint32_t>(ll::usart::CR2::value::stop_1_5_bit << ll::usart::CR2::shift::stop),
            _2 = static_cast<std::uint32_t>(ll::usart::CR2::value::stop_2_bit << ll::usart::CR2::shift::stop),
        };
        enum class MSB_first : std::uint32_t
        {
            disable = 0x0u,
            enable = static_cast<std::uint32_t>(ll::usart::CR2::msbfirst)
        };
        enum class Inversion : std::uint32_t
        {
            disable = 0x0u,
            enable = static_cast<std::uint32_t>(ll::usart::CR2::datainv)
        };

        Word_length word_length;
        Parity parity;
        Stop_bits stop_bits;
        MSB_first msb_first;
        Inversion inversion;
    };

    struct Baudrate
    {
        enum class Auto : std::uint64_t
        {
            _0x7f =
                static_cast<std::uint32_t>(ll::usart::CR2::roten | (ll::usart::CR2::value::abrmod_0x7FF << ll::usart::CR2::shift::abrdmod)),
            _0x55 =
                static_cast<std::uint32_t>(ll::usart::CR2::roten | (ll::usart::CR2::value::abrmod_0x55 << ll::usart::CR2::shift::abrdmod))
        };

        Baudrate() {}
        Baudrate(std::uint32_t value_a)
            : v(static_cast<std::uint64_t>(value_a) << 32u)
        {
        }
        Baudrate(Auto value_a)
            : v(static_cast<std::uint32_t>(value_a))
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

    class Peripheral : private ll::usart::Registers
    {
    public:
        void set_descriptor(const Descriptor& descriptor_a);
        Descriptor get_descriptor() const
        {
            // TODO implement
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

template<> class usart::Transceiver<api::traits::sync> : private ll::usart::Registers
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
        assert(true == xmcu::bit::flag::is(this->isr, ll::usart::ISR::teack));

        std::size_t sent = 0;

        while (sent < data_a.size())
        {
            if (true == xmcu::bit::flag::is(this->isr, ll::usart::ISR::txe))
            {
                this->tdr = data_a[sent];
                sent++;
            }
        }

        xmcu::bit::wait_for::all_set(this->isr, ll::usart::ISR::tc);
        xmcu::bit::flag::set(&(this->icr), ll::usart::ICR::tccf);

        return sent;
    }
    template<typename Word_t> std::size_t trasmit(std::span<const Word_t> data_a, std::chrono::milliseconds timeout_a)
    {
        assert(true == xmcu::bit::flag::is(this->isr, ll::usart::ISR::teack));

        std::size_t sent = 0;
        const std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + timeout_a;

        while (sent < data_a.size() && std::chrono::steady_clock::now() <= timeout)
        {
            if (true == xmcu::bit::flag::is(this->isr, ll::usart::ISR::txe))
            {
                this->tdr = data_a[sent];
                sent++;
            }
        }

        xmcu::bit::wait_for::all_set(this->isr, ll::usart::ISR::tc);
        xmcu::bit::flag::set(&(this->icr), ll::usart::ICR::tccf);

        return sent;
    }

    template<typename Word_t> std::pair<std::size_t, usart::Error> receive(std::span<Word_t> out_a) const
    {
        assert(true == xmcu::bit::flag::is(this->isr, ll::usart::ISR::reack));

        std::size_t received = 0;
        while (false == xmcu::bit::flag::is(this->isr, ll::usart::ISR::idle) && Error::none == this->get_rx_error())
        {
            if (true == xmcu::bit::flag::is(this->isr, ll::usart::ISR::rxne))
            {
                if (true == xmcu::bit::flag::is(this->isr, ll::usart::ISR::cmf) &&
                    true == xmcu::bit::flag::is(this->cr1, ll::usart::CR1::mme | ll::usart::CR1::wake))
                {
                    xmcu::bit::flag::set(&(this->icr), ll::usart::ICR::cmcf);
                }

                if (received < out_a.size())
                {
                    out_a[received++] = static_cast<Word_t>(this->rdr);
                }
                else
                {
                    xmcu::bit::flag::set(&(this->rqr), ll::usart::RQR::rxfrq);
                }
            }
        }

        xmcu::bit::flag::set(&(this->icr), ll::usart::ICR::idlecf);

        const Error err = this->get_rx_error();

        if (Error::none != err)
        {
            xmcu::bit::flag::set(&(this->icr), ll::usart::ICR::fecf | ll::usart::ICR::necf | ll::usart::ICR::orecf | ll::usart::ICR::pecf);

            return { received, err };
        }

        return { received, Error::none };
    }
    template<typename Word_t>
    std::pair<std::size_t, usart::Error> receive(std::span<Word_t> out_a, std::chrono::milliseconds timeout_a) const
    {
        assert(true == xmcu::bit::flag::is(this->isr, ll::usart::ISR::reack));

        std::size_t received = 0;
        const std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + timeout_a;

        while (false == xmcu::bit::flag::is(this->isr, ll::usart::ISR::idle) && Error::none == this->get_rx_error() &&
               std::chrono::steady_clock::now() <= timeout)
        {
            if (true == xmcu::bit::flag::is(this->isr, ll::usart::ISR::rxne))
            {
                if (true == xmcu::bit::flag::is(this->isr, ll::usart::ISR::cmf) &&
                    true == xmcu::bit::flag::is(this->cr1, ll::usart::CR1::mme | ll::usart::CR1::wake))
                {
                    xmcu::bit::flag::set(&(this->icr), ll::usart::ICR::cmcf);
                }

                if (received < out_a.size())
                {
                    out_a[received++] = static_cast<Word_t>(this->rdr);
                }
                else
                {
                    xmcu::bit::flag::set(&(this->rqr), ll::usart::RQR::rxfrq);
                }
            }
        }

        xmcu::bit::flag::set(&(this->icr), ll::usart::ICR::idlecf);

        const Error err = this->get_rx_error();

        if (Error::none != err)
        {
            xmcu::bit::flag::set(&(this->icr), ll::usart::ICR::fecf | ll::usart::ICR::necf | ll::usart::ICR::orecf | ll::usart::ICR::pecf);

            return { received, err };
        }

        return { received, Error::none };
    }

    Error get_rx_error() const
    {
        return static_cast<Error>(
            xmcu::bit::flag::get(this->isr, ll::usart::ISR::fe | ll::usart::ISR::ne | ll::usart::ISR::ore | ll::usart::ISR::pe));
    }
};
template<> class usart::Transceiver<api::traits::async> : private ll::usart::Registers
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
        static void on_receive(std::uint32_t word_a, Error errors_a, usart::Transceiver<api::traits::async>* p_this_a);
        static std::uint32_t on_transmit(usart::Transceiver<api::traits::async>* p_this_a);

        static void on_event(Event events_a, Error errors_a, usart::Transceiver<api::traits::async>* p_this_a);
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