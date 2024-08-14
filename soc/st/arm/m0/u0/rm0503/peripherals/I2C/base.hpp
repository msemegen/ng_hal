#pragma once

/*
 *	Name: i2c.hpp
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
#define XMCU_I2C1_PRESENT
#define XMCU_I2C2_PRESENT
#define XMCU_I2C3_PRESENT
#define XMCU_I2C4_PRESENT

struct i2c_base : protected xmcu::non_constructible
{
    enum class Id
    {
#if defined XMCU_I2C1_PRESENT
        _1 = I2C1_BASE
#endif
#if defined XMCU_I2C2_PRESENT
        ,
        _2 = I2C2_BASE
#endif
#if defined XMCU_I2C3_PRESENT
        ,
        _3 = I2C3_BASE
#endif
#if defined XMCU_I2C4_PRESENT
        ,
        _4 = I2C4_BASE
#endif
    };

    using enum Id;
};

namespace detail {
template<auto... pins_t> struct I2C_pins
{
    static constexpr bool is(auto value_a)
    {
        return ((value_a == pins_t) || ...);
    }
};

template<i2c_base::Id id_t, gpio::Descriptor<gpio::Mode::alternate> descriptor_t, auto pin_t> struct scl_pin
    : private xmcu::non_constructible
{
    static void configure() = delete;
};
template<i2c_base::Id id_t, gpio::Descriptor<gpio::Mode::alternate> descriptor_t, auto pin_t> struct sda_pin
    : private xmcu::non_constructible
{
    static void configure() = delete;
};
} // namespace detail

// scl pins
constexpr detail::I2C_pins<gpio::A::_9, gpio::B::_6, gpio::B::_8> i2c_1_scl_pins;
constexpr detail::I2C_pins<gpio::A::_7, gpio::A::_9, gpio::B::_3, gpio::B::_6, gpio::B::_8, gpio::B::_10, gpio::B::_13> i2c_2_scl_pins;
constexpr detail::I2C_pins<gpio::A::_7, gpio::B::_3, gpio::C::_0> i2c_3_scl_pins;
constexpr detail::I2C_pins<gpio::B::_6, gpio::B::_10, gpio::C::_0> i2c_4_scl_pins;

template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_2, descriptor_t, gpio::A::_7>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::port<gpio::A, api::traits::sync>()->set_pin_descriptor(gpio::A::_7, 0x3u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_3, descriptor_t, gpio::A::_7>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::port<gpio::A, api::traits::sync>()->set_pin_descriptor(gpio::A::_7, 0x4u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_1, descriptor_t, gpio::A::_9>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::port<gpio::A, api::traits::sync>()->set_pin_descriptor(gpio::A::_9, 0x4u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_2, descriptor_t, gpio::A::_9>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::port<gpio::A, api::traits::sync>()->set_pin_descriptor(gpio::A::_9, 0x5u, descriptor_t);
    }
};

template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_2, descriptor_t, gpio::B::_3>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::port<gpio::B, api::traits::sync>()->set_pin_descriptor(gpio::B::_3, 0x3u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_3, descriptor_t, gpio::B::_3>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::port<gpio::B, api::traits::sync>()->set_pin_descriptor(gpio::B::_3, 0x4u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_1, descriptor_t, gpio::B::_6>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::port<gpio::B, api::traits::sync>()->set_pin_descriptor(gpio::B::_6, 0x4u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_2, descriptor_t, gpio::B::_6>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::port<gpio::B, api::traits::sync>()->set_pin_descriptor(gpio::B::_6, 0x5u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_4, descriptor_t, gpio::B::_6>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::port<gpio::B, api::traits::sync>()->set_pin_descriptor(gpio::B::_6, 0x3u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_1, descriptor_t, gpio::B::_8>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::port<gpio::B, api::traits::sync>()->set_pin_descriptor(gpio::B::_8, 0x4u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_2, descriptor_t, gpio::B::_8>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::port<gpio::B, api::traits::sync>()->set_pin_descriptor(gpio::B::_8, 0x3u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_2, descriptor_t, gpio::B::_10>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::port<gpio::B, api::traits::sync>()->set_pin_descriptor(gpio::B::_10, 0x4u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_4, descriptor_t, gpio::B::_10>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::port<gpio::B, api::traits::sync>()->set_pin_descriptor(gpio::B::_10, 0x3u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_2, descriptor_t, gpio::B::_13>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::port<gpio::B, api::traits::sync>()->set_pin_descriptor(gpio::B::_13, 0x4u, descriptor_t);
    }
};

template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_3, descriptor_t, gpio::C::_0>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::C>());
        gpio::port<gpio::C, api::traits::sync>()->set_pin_descriptor(gpio::C::_0, 0x4u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_4, descriptor_t, gpio::C::_0>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::C>());
        gpio::port<gpio::C, api::traits::sync>()->set_pin_descriptor(gpio::C::_0, 0x2u, descriptor_t);
    }
};

template<i2c_base::Id id_t> constexpr auto get_allowed_scl_pins()
{
    if constexpr (i2c_base::_1 == id_t)
    {
        return i2c_1_scl_pins;
    }
    if constexpr (i2c_base::_2 == id_t)
    {
        return i2c_2_scl_pins;
    }
    if constexpr (i2c_base::_3 == id_t)
    {
        return i2c_3_scl_pins;
    }
    if constexpr (i2c_base::_4 == id_t)
    {
        return i2c_4_scl_pins;
    }
}

// sda pins
constexpr detail::I2C_pins<gpio::A::_10, gpio::B::_7, gpio::B::_9> i2c_1_sda_pins;
constexpr detail::I2C_pins<gpio::A::_6, gpio::A::_10, gpio::B::_4, gpio::B::_7, gpio::B::_9, gpio::B::_11, gpio::B::_14> i2c_2_sda_pins;
constexpr detail::I2C_pins<gpio::A::_6, gpio::B::_4, gpio::C::_1> i2c_3_sda_pins;
constexpr detail::I2C_pins<gpio::B::_7, gpio::B::_11, gpio::C::_1> i2c_4_sda_pins;

template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::sda_pin<i2c_base::_2, descriptor_t, gpio::A::_6>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::port<gpio::A, api::traits::sync>()->set_pin_descriptor(gpio::A::_6, 0x3u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::sda_pin<i2c_base::_3, descriptor_t, gpio::A::_6>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::port<gpio::A, api::traits::sync>()->set_pin_descriptor(gpio::A::_6, 0x4u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::sda_pin<i2c_base::_1, descriptor_t, gpio::A::_10>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::port<gpio::A, api::traits::sync>()->set_pin_descriptor(gpio::A::_10, 0x4u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::sda_pin<i2c_base::_2, descriptor_t, gpio::A::_10>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::port<gpio::A, api::traits::sync>()->set_pin_descriptor(gpio::A::_10, 0x5u, descriptor_t);
    }
};

template<i2c_base::Id id_t> constexpr auto get_allowed_sda_pins()
{
    if constexpr (i2c_base::_1 == id_t)
    {
        return i2c_1_sda_pins;
    }
    if constexpr (i2c_base::_2 == id_t)
    {
        return i2c_2_sda_pins;
    }
    if constexpr (i2c_base::_3 == id_t)
    {
        return i2c_3_sda_pins;
    }
    if constexpr (i2c_base::_4 == id_t)
    {
        return i2c_4_sda_pins;
    }
}
#endif
} // namespace soc::st::arm::m0::u0::rm0503::peripherals