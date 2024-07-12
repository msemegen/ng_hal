#pragma once

/*
 */

// std
#include <type_traits>

// soc
#include <soc/non_constructible.hpp>
#include <soc/st/arm/m0/u0/rm0503/peripherals/GPIO/gpio.hpp>

namespace soc::st::arm::m0::u0::rm0503::peripherals {

#if XMCU_SOC_STM32_MODEL == stm32l0u083rct6u
#define XMCU_I2C1_PRESENT
#define XMCU_I2C2_PRESENT
#define XMCU_I2C3_PRESENT
#define XMCU_I2C4_PRESENT

struct i2c_base : protected non_constructible
{
#if defined XMCU_I2C1_PRESENT
    struct _1
    {
    };
#endif
#if defined XMCU_I2C2_PRESENT
    struct _2
    {
    };
#endif
#if defined XMCU_I2C3_PRESENT
    struct _3
    {
    };
#endif
#if defined XMCU_I2C4_PRESENT
    struct _4
    {
    };
#endif
};

namespace detail {
template<auto... pins_t> struct I2C_pins
{
    static constexpr bool is(auto value_a)
    {
        return ((value_a == pins_t) || ...);
    }
};

template<typename id_t, gpio::Descriptor<gpio::Mode::alternate> descriptor_t, auto pin_t> struct scl_pin : private non_constructible
{
    static void configure() = delete;
};
template<typename id_t, gpio::Descriptor<gpio::Mode::alternate> descriptor_t, auto pin_t> struct sda_pin : private non_constructible
{
    static void configure() = delete;
};
} // namespace detail

// scl pins
constexpr detail::I2C_pins<gpio::A::Pin::_9, gpio::B::Pin::_6, gpio::B::Pin::_8> i2c_1_scl_pins;
constexpr detail::
    I2C_pins<gpio::A::Pin::_7, gpio::A::Pin::_9, gpio::B::Pin::_3, gpio::B::Pin::_6, gpio::B::Pin::_8, gpio::B::Pin::_10, gpio::B::Pin::_13>
        i2c_2_scl_pins;
constexpr detail::I2C_pins<gpio::A::Pin::_7, gpio::B::Pin::_3, gpio::C::Pin::_0> i2c_3_scl_pins;
constexpr detail::I2C_pins<gpio::B::Pin::_6, gpio::B::Pin::_10, gpio::C::Pin::_0> i2c_4_scl_pins;

template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_2, descriptor_t, gpio::A::Pin::_7>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::interface<gpio::A>()->enable(gpio::A::Pin::_7, 0x3u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_3, descriptor_t, gpio::A::Pin::_7>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::interface<gpio::A>()->enable(gpio::A::Pin::_7, 0x4u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_1, descriptor_t, gpio::A::Pin::_9>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::interface<gpio::A>()->enable(gpio::A::Pin::_9, 0x4u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_2, descriptor_t, gpio::A::Pin::_9>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::A>());
        gpio::interface<gpio::A>()->enable(gpio::A::Pin::_9, 0x5u, descriptor_t);
    }
};

template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_2, descriptor_t, gpio::B::Pin::_3>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::interface<gpio::A>()->enable(gpio::B::Pin::_3, 0x3u, descriptor_t);
    }
};
template<gpio::Descriptor<gpio::Mode::alternate> descriptor_t> struct detail::scl_pin<i2c_base::_3, descriptor_t, gpio::B::Pin::_3>
{
    static void configure()
    {
        assert(gpio::clock::is_enabled<gpio::B>());
        gpio::interface<gpio::A>()->enable(gpio::B::Pin::_3, 0x4u, descriptor_t);
    }
};

template<typename id_t> constexpr auto get_allowed_scl_pins()
{
    if constexpr (true == std::is_same_v<i2c_base::_1, id_t>)
    {
        return i2c_1_scl_pins;
    }
    if constexpr (true == std::is_same_v<i2c_base::_2, id_t>)
    {
        return i2c_2_scl_pins;
    }
    if constexpr (true == std::is_same_v<i2c_base::_3, id_t>)
    {
        return i2c_3_scl_pins;
    }
    if constexpr (true == std::is_same_v<i2c_base::_4, id_t>)
    {
        return i2c_4_scl_pins;
    }
}

// sda pins
constexpr detail::I2C_pins<gpio::A::Pin::_10, gpio::B::Pin::_7, gpio::B::Pin::_9> i2c_1_sda_pins;
constexpr detail::I2C_pins<gpio::A::Pin::_6,
                           gpio::A::Pin::_10,
                           gpio::B::Pin::_4,
                           gpio::B::Pin::_7,
                           gpio::B::Pin::_9,
                           gpio::B::Pin::_11,
                           gpio::B::Pin::_14>
    i2c_2_sda_pins;
constexpr detail::I2C_pins<gpio::A::Pin::_6, gpio::B::Pin::_4, gpio::C::Pin::_1> i2c_3_sda_pins;
constexpr detail::I2C_pins<gpio::B::Pin::_7, gpio::B::Pin::_11, gpio::C::Pin::_1> i2c_4_sda_pins;

template<typename id_t> constexpr auto get_allowed_sda_pins()
{
    if constexpr (true == std::is_same_v<i2c_base::_1, id_t>)
    {
        return i2c_1_sda_pins;
    }
    if constexpr (true == std::is_same_v<i2c_base::_2, id_t>)
    {
        return i2c_2_sda_pins;
    }
    if constexpr (true == std::is_same_v<i2c_base::_3, id_t>)
    {
        return i2c_3_sda_pins;
    }
    if constexpr (true == std::is_same_v<i2c_base::_4, id_t>)
    {
        return i2c_4_sda_pins;
    }
}

#endif
} // namespace soc::st::arm::m0::u0::rm0503::peripherals