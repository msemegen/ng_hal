#pragma once

/*
 *	Name: i2c.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <chrono>

// xmcu
#include <xmcu/macros.hpp>
#include <xmcu/non_copyable.hpp>

// soc
#include <soc/st/arm/api.hpp>
#include <soc/st/arm/m0/u0/rm0503/clocks/pclk.hpp>
#include <soc/st/arm/m0/u0/rm0503/clocks/sysclk.hpp>
#include <soc/st/arm/m0/u0/rm0503/oscillators/hsi16.hpp>
#include <soc/st/arm/m0/u0/rm0503/peripherals/I2C/base.hpp>

// clang-format off
// CMSIS
#include DECORATE_INCLUDE_PATH(CMSIS_SOC_FILE)
// clang-format on

namespace soc::st::arm::m0::u0::rm0503::peripherals {
namespace ll {
struct i2c_clock : private xmcu::non_constructible
{
    enum class Stop_mode_activity
    {
        disable,
        enable
    };
    template<typename id_t, typename Source_t> static void enable(Stop_mode_activity stop_mode_activity_a) = delete;
    template<typename id_t> static void disable() = delete;

    template<typename id_t> [[nodiscard]] static bool is_enabled() = delete;
    template<typename id_t, typename Source_t> [[nodiscard]] static bool is_source_selected() = delete;
    template<typename id_t> [[nodiscard]] static Stop_mode_activity get_stop_mode_activity() = delete;
};

struct i2c : public i2c_base
{
    using clock = i2c_clock;

    struct Peripheral : private xmcu::non_copyable
    {
        volatile std::uint32_t cr1;     // control register 1
        volatile std::uint32_t cr2;     // control register 2
        volatile std::uint32_t oar1;    // own address 1 register
        volatile std::uint32_t oar2;    // own address 2 register
        volatile std::uint32_t timingr; // timing register
    private:
        volatile std::uint32_t reserved;

    public:
        volatile std::uint32_t isr; // interrupt and status register
        volatile std::uint32_t icr; // interrupt clear register
    private:
        volatile std::uint32_t reserved0;

    public:
        volatile std::uint32_t rxdr; // receive data register
        volatile std::uint32_t txdr; // transmit data register
    };

    template<typename id_t> [[nodiscard]] constexpr static Peripheral* interface() = delete;
};

#if defined XMCU_I2C1_PRESENT
template<> [[nodiscard]] inline constexpr i2c::Peripheral* i2c::interface<i2c::_1>()
{
    return reinterpret_cast<i2c::Peripheral*>(I2C1_BASE);
}

template<> inline void i2c_clock::enable<i2c_base::_1, oscillators::hsi16>(Stop_mode_activity stop_mode_activity_a)
{
    switch (stop_mode_activity_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C1SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C1SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_I2C1SEL, RCC_CCIPR_I2C1SEL_1);
    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_I2C1EN);
}
template<> [[nodiscard]] bool i2c_clock::is_source_selected<i2c::_1, oscillators::hsi16>()
{
    return false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_I2C1SEL_0) && true == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_I2C1SEL_1);
}
template<> inline void i2c_clock::enable<i2c_base::_1, clocks::sysclk>(Stop_mode_activity stop_mode_activity_a)
{
    switch (stop_mode_activity_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C1SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C1SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_I2C1SEL, RCC_CCIPR_I2C1SEL_0);
    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_I2C1EN);
}
template<> [[nodiscard]] bool i2c_clock::is_source_selected<i2c::_1, clocks::sysclk>()
{
    return true == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_I2C1SEL_0) && false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_I2C1SEL_1);
}
template<> inline void i2c_clock::enable<i2c_base::_1, clocks::pclk>(Stop_mode_activity stop_mode_activity_a)
{
    switch (stop_mode_activity_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C1SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C1SMEN);
            break;
    }

    xmcu::bit::flag::clear(&(RCC->CCIPR), RCC_CCIPR_I2C1SEL);
    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_I2C1EN);
}
template<> [[nodiscard]] bool i2c_clock::is_source_selected<i2c::_1, clocks::pclk>()
{
    return false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_I2C1SEL_0 | RCC_CCIPR_I2C1SEL_1);
}
template<> inline void i2c_clock::disable<i2c::_1>()
{
    xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C1SMEN);
    xmcu::bit::flag::clear(&(RCC->CCIPR), RCC_CCIPR_I2C1SEL);
    xmcu::bit::flag::clear(&(RCC->APBENR1), RCC_APBENR1_I2C1EN);
}
template<> [[nodiscard]] inline bool i2c_clock::is_enabled<i2c_base::_1>()
{
    return xmcu::bit::flag::is(RCC->APBENR1, RCC_APBENR1_I2C1EN);
}
template<> [[nodiscard]] inline i2c_clock::Stop_mode_activity i2c_clock::get_stop_mode_activity<i2c_base::_1>()
{
    return true == xmcu::bit::flag::is(RCC->APBSMENR1, RCC_APBSMENR1_I2C1SMEN) ? Stop_mode_activity::enable : Stop_mode_activity::disable;
}
#endif
#if defined XMCU_I2C2_PRESENT
template<> [[nodiscard]] constexpr i2c::Peripheral* i2c::interface<i2c::_2>()
{
    return reinterpret_cast<i2c::Peripheral*>(I2C2_BASE);
}

template<> inline void i2c_clock::enable<i2c_base::_2, clocks::pclk>(Stop_mode_activity stop_mode_activity_a)
{
    switch (stop_mode_activity_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C2SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C2SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_I2C2EN);
}
template<> [[nodiscard]] bool i2c_clock::is_source_selected<i2c::_2, clocks::pclk>()
{
    return true;
}
template<> inline void i2c_clock::disable<i2c::_2>()
{
    xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C2SMEN);
    xmcu::bit::flag::clear(&(RCC->APBENR1), RCC_APBENR1_I2C2EN);
}
template<> [[nodiscard]] inline bool i2c_clock::is_enabled<i2c_base::_2>()
{
    return xmcu::bit::flag::is(RCC->APBENR1, RCC_APBENR1_I2C2EN);
}
template<> [[nodiscard]] inline i2c_clock::Stop_mode_activity i2c_clock::get_stop_mode_activity<i2c_base::_2>()
{
    return true == xmcu::bit::flag::is(RCC->APBSMENR1, RCC_APBSMENR1_I2C2SMEN) ? Stop_mode_activity::enable : Stop_mode_activity::disable;
}
#endif
#if defined XMCU_I2C3_PRESENT
template<> [[nodiscard]] constexpr i2c::Peripheral* i2c::interface<i2c::_3>()
{
    return reinterpret_cast<i2c::Peripheral*>(I2C3_BASE);
}

template<> inline void i2c_clock::enable<i2c_base::_3, oscillators::hsi16>(Stop_mode_activity stop_mode_activity_a)
{
    switch (stop_mode_activity_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C3SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C3SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_I2C3SEL, RCC_CCIPR_I2C3SEL_1);
    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_I2C3EN);
}
template<> [[nodiscard]] bool i2c_clock::is_source_selected<i2c::_3, oscillators::hsi16>()
{
    return false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_I2C3SEL_0) && true == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_I2C3SEL_1);
}
template<> inline void i2c_clock::enable<i2c_base::_3, clocks::sysclk>(Stop_mode_activity stop_mode_activity_a)
{
    switch (stop_mode_activity_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C3SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C3SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_I2C3SEL, RCC_CCIPR_I2C3SEL_0);
    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_I2C3EN);
}
template<> [[nodiscard]] bool i2c_clock::is_source_selected<i2c::_3, clocks::sysclk>()
{
    return true == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_I2C3SEL_0) && false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_I2C3SEL_1);
}
template<> inline void i2c_clock::enable<i2c_base::_3, clocks::pclk>(Stop_mode_activity stop_mode_activity_a)
{
    switch (stop_mode_activity_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C3SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C3SMEN);
            break;
    }

    xmcu::bit::flag::clear(&(RCC->CCIPR), RCC_CCIPR_I2C3SEL);
    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_I2C3EN);
}
template<> [[nodiscard]] bool i2c_clock::is_source_selected<i2c::_3, clocks::pclk>()
{
    return false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_I2C3SEL_0 | RCC_CCIPR_I2C3SEL_1);
}
template<> inline void i2c_clock::disable<i2c::_3>()
{
    xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C3SMEN);
    xmcu::bit::flag::clear(&(RCC->CCIPR), RCC_CCIPR_I2C3SEL);
    xmcu::bit::flag::clear(&(RCC->APBENR1), RCC_APBENR1_I2C3EN);
}
template<> [[nodiscard]] inline bool i2c_clock::is_enabled<i2c_base::_3>()
{
    return xmcu::bit::flag::is(RCC->APBENR1, RCC_APBENR1_I2C3EN);
}
template<> [[nodiscard]] inline i2c_clock::Stop_mode_activity i2c_clock::get_stop_mode_activity<i2c_base::_3>()
{
    return true == xmcu::bit::flag::is(RCC->APBSMENR1, RCC_APBSMENR1_I2C3SMEN) ? Stop_mode_activity::enable : Stop_mode_activity::disable;
}
#endif
#if defined XMCU_I2C4_PRESENT
template<> [[nodiscard]] constexpr i2c::Peripheral* i2c::interface<i2c::_4>()
{
    return reinterpret_cast<i2c::Peripheral*>(I2C4_BASE);
}

template<> inline void i2c_clock::enable<i2c_base::_4, clocks::pclk>(Stop_mode_activity stop_mode_activity_a)
{
    switch (stop_mode_activity_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C4SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C4SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_I2C4EN);
}
template<> [[nodiscard]] bool i2c_clock::is_source_selected<i2c::_4, clocks::pclk>()
{
    return true;
}
template<> inline void i2c_clock::disable<i2c::_4>()
{
    xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_I2C4SMEN);
    xmcu::bit::flag::clear(&(RCC->APBENR1), RCC_APBENR1_I2C4EN);
}
template<> [[nodiscard]] inline bool i2c_clock::is_enabled<i2c_base::_4>()
{
    return xmcu::bit::flag::is(RCC->APBENR1, RCC_APBENR1_I2C4EN);
}
template<> [[nodiscard]] inline i2c_clock::Stop_mode_activity i2c_clock::get_stop_mode_activity<i2c_base::_4>()
{
    return true == xmcu::bit::flag::is(RCC->APBSMENR1, RCC_APBSMENR1_I2C4SMEN) ? Stop_mode_activity::enable : Stop_mode_activity::disable;
}
#endif
} // namespace ll

struct i2c : public i2c_base
{
    using clock = ll::i2c_clock;

    struct Descriptor
    {
        enum class Mode : std::uint64_t
        {
            master = 0x1u,
            slave = 0x2u
        };

        struct Master
        {
        };

        struct Slave
        {
            std::uint8_t address;
        };

        Mode mode;
    };

    struct traits : private xmcu::non_constructible
    {
        template<auto sda_pin_t,
                 gpio::Descriptor<gpio::Mode::alternate> sda_descriptor_t,
                 auto scl_pin_t,
                 gpio::Descriptor<gpio::Mode::alternate> scl_descriptor_t>
        struct half_duplex
        {
            constexpr static auto sda_pin = sda_pin_t;
            constexpr static auto sda_descriptor = sda_descriptor_t;
            constexpr static auto scl_pin = scl_pin_t;
            constexpr static auto scl_descriptor = scl_descriptor_t;
        };
    };

    class Peripheral : private ll::i2c::Peripheral
    {
    public:
        void set_descriptor(const Descriptor& descriptor_a) {}

        bool enable(std::chrono::milliseconds timeout_a);
        bool disable(std::chrono::milliseconds timeout_a);
    };

    template<api::traits trait_t> class Transceiver : private non_constructible
    {
    };

    template<typename id_t> [[nodiscard]] constexpr static Peripheral* interface() = delete;

    template<typename id_t, typename transmission_mode_t> static void set_traits()
    {
        static_assert(get_allowed_sda_pins<id_t>().is(transmission_mode_t::sda_pin), "incorrect sda pin");
        static_assert(get_allowed_scl_pins<id_t>().is(transmission_mode_t::scl_pin), "incorrect scl pin");

        detail::sda_pin<id_t, transmission_mode_t::sda_descriptor, transmission_mode_t::sda_pin>::configure();
        detail::scl_pin<id_t, transmission_mode_t::scl_descriptor, transmission_mode_t::scl_pin>::configure();
    }
};

constexpr i2c::Descriptor::Mode operator|(i2c::Descriptor::Mode mode_a, const i2c::Descriptor::Master& master_a)
{
    assert(i2c::Descriptor::Mode::master == mode_a);
    return {};
}
constexpr i2c::Descriptor::Mode operator|(i2c::Descriptor::Mode mode_a, const i2c::Descriptor::Slave& slave_a)
{
    assert(i2c::Descriptor::Mode::slave == mode_a);
    return {};
}

#if defined XMCU_I2C1_PRESENT
template<> [[nodiscard]] inline constexpr i2c::Peripheral* i2c::interface<i2c::_1>()
{
    return reinterpret_cast<i2c::Peripheral*>(I2C1_BASE);
}
#endif
#if defined XMCU_I2C2_PRESENT
template<> [[nodiscard]] inline constexpr i2c::Peripheral* i2c::interface<i2c::_2>()
{
    return reinterpret_cast<i2c::Peripheral*>(I2C2_BASE);
}
#endif
#if defined XMCU_I2C3_PRESENT
template<> [[nodiscard]] inline constexpr i2c::Peripheral* i2c::interface<i2c::_3>()
{
    return reinterpret_cast<i2c::Peripheral*>(I2C3_BASE);
}
#endif
#if defined XMCU_I2C4_PRESENT
template<> [[nodiscard]] inline constexpr i2c::Peripheral* i2c::interface<i2c::_4>()
{
    return reinterpret_cast<i2c::Peripheral*>(I2C4_BASE);
}
#endif
} // namespace soc::st::arm::m0::u0::rm0503::peripherals