#pragma once

/*
 *	Name: base.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <type_traits>

// xmcu
#include <xmcu/non_constructible.hpp>

// soc
#include <soc/st/arm/m0/u0/rm0503/peripherals/GPIO/gpio.hpp>

namespace soc::st::arm::m0::u0::rm0503::peripherals {
#if XMCU_SOC_STM32_MODEL == stm32l0u083rct6u
#define XMCU_USART1_PRESENT
#define XMCU_USART2_PRESENT
#define XMCU_USART3_PRESENT
#define XMCU_USART4_PRESENT

struct usart_base : protected xmcu::non_constructible
{
    enum class Id
    {
#if defined XMCU_USART1_PRESENT
        _1
#endif
#if defined XMCU_USART2_PRESENT
        ,
        _2
#endif
#if defined XMCU_USART3_PRESENT
        ,
        _3
#endif
#if defined XMCU_USART4_PRESENT
        ,
        _4
#endif
    };

    using enum Id;
};

namespace detail {
template<auto... pins_t> struct USART_pins
{
    static constexpr bool is(auto value_a)
    {
        return ((value_a == pins_t) || ...);
    }
};

template<usart_base::Id id_t, gpio::Descriptor<gpio::Mode::alternate> descriptor_t, auto pin_t> struct rx_pin
    : private xmcu::non_constructible
{
    static void configure() = delete;
};
template<usart_base::Id id_t, gpio::Descriptor<gpio::Mode::alternate> descriptor_t, auto pin_t> struct tx_pin
    : private xmcu::non_constructible
{
    static void configure() = delete;
};
template<usart_base::Id id_t, gpio::Descriptor<gpio::Mode::alternate> descriptor_t, auto pin_t> struct clk_pin
    : private xmcu::non_constructible
{
    static void configure() = delete;
};
template<usart_base::Id id_t, gpio::Descriptor<gpio::Mode::alternate> descriptor_t, auto pin_t> struct cts_pin
    : private xmcu::non_constructible
{
    static void configure() = delete;
};
template<usart_base::Id id_t, gpio::Descriptor<gpio::Mode::alternate> descriptor_t, auto pin_t> struct rts_pin
    : private xmcu::non_constructible
{
    static void configure() = delete;
};
} // namespace detail

// rx pins
constexpr detail::USART_pins<gpio::A::Pin::_10, gpio::B::Pin::_7> usart_1_rx_pins;
constexpr detail::USART_pins<gpio::A::Pin::_3, gpio::A::Pin::_15> usart_2_rx_pins;
constexpr detail::USART_pins<gpio::A::Pin::_7, gpio::B::Pin::_9, gpio::B::Pin::_11, gpio::C::Pin::_5, gpio::C::Pin::_11> usart_3_rx_pins;
constexpr detail::USART_pins<gpio::A::Pin::_1, gpio::C::Pin::_11> usart_4_rx_pins;

template<usart_base::Id id_t> constexpr auto get_allowed_rx_pins()
{
    if constexpr (usart_base::_1 == id_t)
    {
        return usart_1_rx_pins;
    }
    if constexpr (usart_base::_2 == id_t)
    {
        return usart_2_rx_pins;
    }
    if constexpr (usart_base::_3 == id_t)
    {
        return usart_3_rx_pins;
    }
    if constexpr (usart_base::_4 == id_t)
    {
        return usart_4_rx_pins;
    }
}

template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rx_pin<usart_base::_4, descriptor_t, gpio::A::Pin::_1>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::interface<gpio::A>()->enable(gpio::A::Pin::_1, 0x8u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rx_pin<usart_base::_2, descriptor_t, gpio::A::Pin::_3>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::interface<gpio::A>()->enable(gpio::A::Pin::_3, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rx_pin<usart_base::_3, descriptor_t, gpio::A::Pin::_7>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::interface<gpio::A>()->enable(gpio::A::Pin::_7, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rx_pin<usart_base::_1, descriptor_t, gpio::A::Pin::_10>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::interface<gpio::A>()->enable(gpio::A::Pin::_10, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rx_pin<usart_base::_2, descriptor_t, gpio::A::Pin::_15>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::interface<gpio::A>()->enable(gpio::A::Pin::_15, 0x3u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rx_pin<usart_base::_1, descriptor_t, gpio::B::Pin::_7>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::interface<gpio::B>()->enable(gpio::B::Pin::_7, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rx_pin<usart_base::_3, descriptor_t, gpio::B::Pin::_9>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::interface<gpio::B>()->enable(gpio::B::Pin::_9, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rx_pin<usart_base::_3, descriptor_t, gpio::B::Pin::_11>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::interface<gpio::B>()->enable(gpio::B::Pin::_11, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rx_pin<usart_base::_3, descriptor_t, gpio::C::Pin::_5>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::C>());
        gpio::interface<gpio::C>()->enable(gpio::C::Pin::_5, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rx_pin<usart_base::_3, descriptor_t, gpio::C::Pin::_11>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::C>());
        gpio::interface<gpio::C>()->enable(gpio::C::Pin::_11, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rx_pin<usart_base::_4, descriptor_t, gpio::C::Pin::_11>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::C>());
        gpio::interface<gpio::C>()->enable(gpio::C::Pin::_11, 0x8u, descriptor_t);
    }
};

// tx pins
constexpr detail::USART_pins<gpio::A::Pin::_9, gpio::B::Pin::_6> usart_1_tx_pins;
constexpr detail::USART_pins<gpio::A::Pin::_2> usart_2_tx_pins;
constexpr detail::USART_pins<gpio::A::Pin::_5, gpio::B::Pin::_8, gpio::B::Pin::_10, gpio::C::Pin::_4, gpio::C::Pin::_10> usart_3_tx_pins;
constexpr detail::USART_pins<gpio::A::Pin::_0, gpio::C::Pin::_10> usart_4_tx_pins;

template<usart_base::Id id_t> constexpr auto get_allowed_tx_pins()
{
    if constexpr (usart_base::_1 == id_t)
    {
        return usart_1_tx_pins;
    }
    if constexpr (usart_base::_2 == id_t)
    {
        return usart_2_tx_pins;
    }
    if constexpr (usart_base::_3 == id_t)
    {
        return usart_3_tx_pins;
    }
    if constexpr (usart_base::_4 == id_t)
    {
        return usart_4_tx_pins;
    }
}

template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::tx_pin<usart_base::_4, descriptor_t, gpio::A::Pin::_0>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::interface<gpio::A>()->enable(gpio::A::Pin::_0, 0x8u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::tx_pin<usart_base::_2, descriptor_t, gpio::A::Pin::_2>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::interface<gpio::A>()->enable(gpio::A::Pin::_2, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::tx_pin<usart_base::_3, descriptor_t, gpio::A::Pin::_5>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::interface<gpio::A>()->enable(gpio::A::Pin::_5, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::tx_pin<usart_base::_1, descriptor_t, gpio::A::Pin::_9>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::interface<gpio::A>()->enable(gpio::A::Pin::_9, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::tx_pin<usart_base::_1, descriptor_t, gpio::B::Pin::_6>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::interface<gpio::B>()->enable(gpio::B::Pin::_6, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::tx_pin<usart_base::_3, descriptor_t, gpio::B::Pin::_8>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::interface<gpio::B>()->enable(gpio::B::Pin::_8, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::tx_pin<usart_base::_3, descriptor_t, gpio::B::Pin::_10>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::interface<gpio::B>()->enable(gpio::B::Pin::_10, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::tx_pin<usart_base::_3, descriptor_t, gpio::C::Pin::_4>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::C>());
        gpio::interface<gpio::C>()->enable(gpio::C::Pin::_4, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::tx_pin<usart_base::_3, descriptor_t, gpio::C::Pin::_10>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::C>());
        gpio::interface<gpio::C>()->enable(gpio::C::Pin::_10, 0x7u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::tx_pin<usart_base::_4, descriptor_t, gpio::C::Pin::_10>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::C>());
        gpio::interface<gpio::C>()->enable(gpio::C::Pin::_10, 0x8u, descriptor_t);
    }
};

// clock pins
constexpr detail::USART_pins<gpio::A::Pin::_8, gpio::B::Pin::_5> usart_1_ck_pins;
constexpr detail::USART_pins<gpio::A::Pin::_4> usart_2_ck_pins;
constexpr detail::USART_pins<> usart_3_ck_pins;
constexpr detail::USART_pins<gpio::C::Pin::_3, gpio::C::Pin::_12> usart_4_ck_pins;

template<usart_base::Id id_t> constexpr auto get_allowed_ck_pins()
{
    if constexpr (usart_base::_1 == id_t)
    {
        return usart_1_ck_pins;
    }
    if constexpr (usart_base::_2 == id_t)
    {
        return usart_2_ck_pins;
    }
    if constexpr (usart_base::_3 == id_t)
    {
        return usart_3_ck_pins;
    }
    if constexpr (usart_base::_4 == id_t)
    {
        return usart_4_ck_pins;
    }
}

template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::clk_pin<usart_base::_2, descriptor_t, gpio::A::Pin::_4>
{
    static void configure() {}
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::clk_pin<usart_base::_1, descriptor_t, gpio::A::Pin::_8>
{
    static void configure() {}
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::clk_pin<usart_base::_1, descriptor_t, gpio::B::Pin::_5>
{
    static void configure() {}
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::clk_pin<usart_base::_4, descriptor_t, gpio::C::Pin::_3>
{
    static void configure() {}
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::clk_pin<usart_base::_4, descriptor_t, gpio::C::Pin::_12>
{
    static void configure() {}
};

// hw flow control cts pins
constexpr detail::USART_pins<gpio::A::Pin::_11, gpio::B::Pin::_4> usart_1_cts_pins;
constexpr detail::USART_pins<> usart_2_cts_pins;
constexpr detail::USART_pins<> usart_3_cts_pins;
constexpr detail::USART_pins<gpio::B::Pin::_7> usart_4_cts_pins;

template<usart_base::Id id_t> constexpr auto get_allowed_cts_pins()
{
    if constexpr (usart_base::_1 == id_t)
    {
        return usart_1_cts_pins;
    }
    if constexpr (usart_base::_2 == id_t)
    {
        return usart_2_cts_pins;
    }
    if constexpr (usart_base::_3 == id_t)
    {
        return usart_3_cts_pins;
    }
    if constexpr (usart_base::_4 == id_t)
    {
        return usart_4_cts_pins;
    }
}
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::cts_pin<usart_base::_1, descriptor_t, gpio::A::Pin::_11>
{
    static void configure() {}
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::cts_pin<usart_base::_1, descriptor_t, gpio::B::Pin::_4>
{
    static void configure() {}
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::cts_pin<usart_base::_4, descriptor_t, gpio::B::Pin::_7>
{
    static void configure() {}
};

// hw flow control rts pins
constexpr detail::USART_pins<gpio::A::Pin::_12, gpio::B::Pin::_3> usart_1_rts_pins;
constexpr detail::USART_pins<> usart_2_rts_pins;
constexpr detail::USART_pins<gpio::D::Pin::_2> usart_3_rts_pins;
constexpr detail::USART_pins<gpio::A::Pin::_15> usart_4_rts_pins;

template<usart_base::Id id_t> constexpr auto get_allowed_rts_pins()
{
    if constexpr (usart_base::_1 == id_t)
    {
        return usart_1_rts_pins;
    }
    if constexpr (usart_base::_2 == id_t)
    {
        return usart_2_rts_pins;
    }
    if constexpr (usart_base::_3 == id_t)
    {
        return usart_3_rts_pins;
    }
    if constexpr (usart_base::_4 == id_t)
    {
        return usart_4_rts_pins;
    }
}

template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rts_pin<usart_base::_1, descriptor_t, gpio::A::Pin::_12>
{
    static void configure() {}
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rts_pin<usart_base::_4, descriptor_t, gpio::A::Pin::_15>
{
    static void configure() {}
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rts_pin<usart_base::_1, descriptor_t, gpio::B::Pin::_3>
{
    static void configure() {}
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::rts_pin<usart_base::_3, descriptor_t, gpio::D::Pin::_2>
{
    static void configure() {}
};

template<usart_base::Id id_t> constexpr inline auto get_usart_port_address()
{
    if constexpr (usart_base::_1 == id_t)
    {
        return USART1_BASE;
    }
    if constexpr (usart_base::_2 == id_t)
    {
        return USART2_BASE;
    }
    if constexpr (usart_base::_3 == id_t)
    {
        return USART3_BASE;
    }
    if constexpr (usart_base::_4 == id_t)
    {
        return USART4_BASE;
    }
}
#endif
} // namespace soc::st::arm::m0::u0::rm0503::peripherals