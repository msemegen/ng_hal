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
    template<i2c_base::Id id_t, typename Source_t> static void enable(Stop_mode_activity stop_mode_activity_a) = delete;
    template<i2c_base::Id id_t> static void disable() = delete;

    template<i2c_base::Id id_t> [[nodiscard]] static bool is_enabled() = delete;
    template<i2c_base::Id id_t, typename Source_t> [[nodiscard]] static bool is_source_selected() = delete;
    template<i2c_base::Id id_t> [[nodiscard]] static Stop_mode_activity get_stop_mode_activity() = delete;
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

    template<i2c::Id id_t> [[nodiscard]] constexpr static Peripheral* peripheral() = delete;
};

#if defined XMCU_I2C1_PRESENT
template<> [[nodiscard]] inline constexpr i2c::Peripheral* i2c::peripheral<i2c::_1>()
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
template<> [[nodiscard]] inline bool i2c_clock::is_source_selected<i2c::_1, oscillators::hsi16>()
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
template<> [[nodiscard]] inline bool i2c_clock::is_source_selected<i2c::_1, clocks::sysclk>()
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
template<> [[nodiscard]] inline bool i2c_clock::is_source_selected<i2c::_1, clocks::pclk>()
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
template<> [[nodiscard]] constexpr i2c::Peripheral* i2c::peripheral<i2c::_2>()
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
template<> [[nodiscard]] inline bool i2c_clock::is_source_selected<i2c::_2, clocks::pclk>()
{
    return true;
}
template<> [[nodiscard]] constexpr bool i2c_clock::is_source_selected<i2c::_2, oscillators::hsi16>()
{
    return false;
}
template<> [[nodiscard]] constexpr bool i2c_clock::is_source_selected<i2c::_2, clocks::sysclk>()
{
    return false;
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
template<> [[nodiscard]] constexpr i2c::Peripheral* i2c::peripheral<i2c::_3>()
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
template<> [[nodiscard]] inline bool i2c_clock::is_source_selected<i2c::_3, oscillators::hsi16>()
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
template<> [[nodiscard]] inline bool i2c_clock::is_source_selected<i2c::_3, clocks::sysclk>()
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
template<> [[nodiscard]] inline bool i2c_clock::is_source_selected<i2c::_3, clocks::pclk>()
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
template<> [[nodiscard]] constexpr i2c::Peripheral* i2c::peripheral<i2c::_4>()
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
template<> [[nodiscard]] inline bool i2c_clock::is_source_selected<i2c::_4, clocks::pclk>()
{
    return true;
}
template<> [[nodiscard]] constexpr bool i2c_clock::is_source_selected<i2c::_4, oscillators::hsi16>()
{
    return false;
}
template<> [[nodiscard]] constexpr bool i2c_clock::is_source_selected<i2c::_4, clocks::sysclk>()
{
    return false;
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

    enum class Kind : std::uint64_t
    {
        master = 0x1u,
        slave = 0x2u
    };

    using enum Kind;

    enum class Fast_mode_plus : std::uint32_t
    {
        disable = 0x0u,
        enable = I2C_CR1_FMP
    };
    enum class General_call : std::uint32_t
    {
        disable = 0x0u,
        enable = I2C_CR1_GCEN
    };
    enum class Clock_streetch : std::uint32_t
    {
        disable = I2C_CR1_NOSTRETCH,
        enable = 0x0u
    };
    enum class Wakeup_from_stop : std::uint32_t
    {
        disable = 0x0u,
        enable = I2C_CR1_WUPEN
    };
    enum class Address_kind : std::uint32_t
    {
        _7bit = 0x0u,
        _10bit = 0xFFFu
    };
    enum class Analog_noise_filter : std::uint32_t
    {
        disable = I2C_CR1_ANFOFF,
        enable = 0x0u
    };

    enum class Error : std::uint32_t
    {
        none = 0x0u,
        arbitration_lost = I2C_ISR_ARLO,
        frame_misplaced = I2C_ISR_BERR,
        nack = I2C_ISR_NACKF,
        overrun = I2C_ISR_OVR
    };

    template<Kind kind_t> struct Descriptor : private xmcu::non_constructible
    {
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

    template<Kind kind_t> class Peripheral : private xmcu::non_constructible
    {
    };

    template<api::traits trait_t, Kind kind_t> class Transceiver : private non_constructible
    {
    };

    template<i2c::Id id_t, Kind kind_t> [[nodiscard]] constexpr static Peripheral<kind_t>* peripheral() = delete;

    template<i2c::Id id_t, typename transmission_mode_t> static void set_traits()
    {
        static_assert(get_allowed_sda_pins<id_t>().is(transmission_mode_t::sda_pin), "incorrect sda pin");
        static_assert(get_allowed_scl_pins<id_t>().is(transmission_mode_t::scl_pin), "incorrect scl pin");

        detail::sda_pin<id_t, transmission_mode_t::sda_descriptor, transmission_mode_t::sda_pin>::configure();
        detail::scl_pin<id_t, transmission_mode_t::scl_descriptor, transmission_mode_t::scl_pin>::configure();
    }
};

template<> struct i2c::Descriptor<i2c::master>
{
    i2c::Fast_mode_plus fast_mode_plus;
    i2c::Analog_noise_filter analog_noise_filter;
    i2c::Wakeup_from_stop wakeup_from_stop;
    i2c::Address_kind address_kind;
    std::uint32_t timing;
    std::uint8_t digital_noise_filter;
};
template<> struct i2c::Descriptor<i2c::slave>
{
    i2c::Fast_mode_plus fast_mode_plus;
    i2c::Analog_noise_filter analog_noise_filter;
    i2c::General_call general_call;
    i2c::Wakeup_from_stop wakeup_from_stop;
    i2c::Address_kind address_kind;
    std::uint16_t address;
    std::uint32_t timing;
    std::uint8_t digital_noise_filter;
};

constexpr std::uint16_t operator|(std::uint16_t address_value_a, i2c::Address_kind kind_a)
{
    return static_cast<std::uint16_t>(kind_a) | address_value_a;
}

#if defined XMCU_I2C1_PRESENT
template<> [[nodiscard]] inline constexpr i2c::Peripheral<i2c::master>* i2c::peripheral<i2c::_1, i2c::master>()
{
    return reinterpret_cast<i2c::Peripheral<i2c::master>*>(I2C1_BASE);
}
template<> [[nodiscard]] inline constexpr i2c::Peripheral<i2c::slave>* i2c::peripheral<i2c::_1, i2c::slave>()
{
    return reinterpret_cast<i2c::Peripheral<i2c::slave>*>(I2C1_BASE);
}
#endif
#if defined XMCU_I2C2_PRESENT
template<> [[nodiscard]] inline constexpr i2c::Peripheral<i2c::master>* i2c::peripheral<i2c::_2, i2c::master>()
{
    return reinterpret_cast<i2c::Peripheral<i2c::master>*>(I2C2_BASE);
}
template<> [[nodiscard]] inline constexpr i2c::Peripheral<i2c::slave>* i2c::peripheral<i2c::_2, i2c::slave>()
{
    return reinterpret_cast<i2c::Peripheral<i2c::slave>*>(I2C2_BASE);
}
#endif
#if defined XMCU_I2C3_PRESENT
template<> [[nodiscard]] inline constexpr i2c::Peripheral<i2c::master>* i2c::peripheral<i2c::_3, i2c::master>()
{
    return reinterpret_cast<i2c::Peripheral<i2c::master>*>(I2C3_BASE);
}
template<> [[nodiscard]] inline constexpr i2c::Peripheral<i2c::slave>* i2c::peripheral<i2c::_3, i2c::slave>()
{
    return reinterpret_cast<i2c::Peripheral<i2c::slave>*>(I2C3_BASE);
}
#endif
#if defined XMCU_I2C4_PRESENT
template<> [[nodiscard]] inline constexpr i2c::Peripheral<i2c::master>* i2c::peripheral<i2c::_4, i2c::master>()
{
    return reinterpret_cast<i2c::Peripheral<i2c::master>*>(I2C4_BASE);
}
template<> [[nodiscard]] inline constexpr i2c::Peripheral<i2c::slave>* i2c::peripheral<i2c::_4, i2c::slave>()
{
    return reinterpret_cast<i2c::Peripheral<i2c::slave>*>(I2C4_BASE);
}
#endif

template<> class i2c::Peripheral<i2c::master> : private ll::i2c::Peripheral
{
public:
    void set_descriptor(const i2c::Descriptor<i2c::master>& descriptor_a);

    void enable(std::chrono::milliseconds timeout_a)
    {
        xmcu::bit::flag::set(&(this->cr1), I2C_CR1_PE);
        xmcu::bit::wait_for::all_set(this->cr1, I2C_CR1_PE);
    }
    void disable()
    {
        xmcu::bit::flag::clear(&(this->cr1), I2C_CR1_PE);
    }

    template<typename Type_t> Type_t* view() const = delete;
};

template<> class i2c::Peripheral<i2c::slave> : private ll::i2c::Peripheral
{
public:
    void set_descriptor(const i2c::Descriptor<i2c::slave>& descriptor_a);

    void enable(std::chrono::milliseconds timeout_a)
    {
        xmcu::bit::flag::set(&(this->cr1), I2C_CR1_PE);
        xmcu::bit::wait_for::all_set(this->cr1, I2C_CR1_PE);
    }
    void disable()
    {
        xmcu::bit::flag::clear(&(this->cr1), I2C_CR1_PE);
    }

    template<typename Type_t> Type_t* view() const = delete;
};

template<> class i2c::Transceiver<api::traits::sync, i2c::master> : private ll::i2c::Peripheral
{
public:
    std::pair<std::size_t, i2c::Error> transmit(std::uint16_t address_a, const std::span<std::uint8_t> data_a)
    {
        std::size_t remaining = data_a.size();

        xmcu::bit::flag::set(&(this->cr2),
                             I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RD_WRN,
                             (address_a & I2C_CR2_SADD) | data_length_mask(remaining) | I2C_CR2_START);

        while (remaining != 0u && false == xmcu::bit::flag::is(this->isr, I2C_ISR_NACKF | I2C_ISR_ARLO | I2C_ISR_BERR | I2C_ISR_OVR))
        {
            const std::size_t i = data_a.size() - remaining;
            if (true == xmcu::bit::flag::is(this->isr, I2C_ISR_TXE))
            {
                this->txdr = data_a[i];
                remaining--;
            }

            if (i > 255u && xmcu::bit::flag::is(this->cr2, I2C_CR2_RELOAD))
            {
                xmcu::bit::flag::set(&(this->cr2),
                                     I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RD_WRN,
                                     (address_a & I2C_CR2_SADD) | data_length_mask(remaining) | I2C_CR2_START);
            }
        }

        xmcu::bit::wait_for::all_set(this->isr, I2C_ISR_STOPF);

        const Error err = static_cast<Error>(this->isr & (I2C_ISR_NACKF | I2C_ISR_ARLO | I2C_ISR_BERR | I2C_ISR_OVR));

        if (Error::none != err)
        {
            xmcu::bit::flag::set(&(this->icr), I2C_ICR_NACKCF | I2C_ICR_ARLOCF | I2C_ICR_BERRCF | I2C_ICR_OVRCF);
        }

        return { data_a.size() - remaining, err };
    }
    std::pair<std::size_t, i2c::Error>
    transmit(std::uint16_t address_a, const std::span<std::uint8_t> data_a, std::chrono::milliseconds timeout_a)
    {
        const std::chrono::steady_clock::time_point end_time_point = std::chrono::steady_clock::now() + timeout_a;

        std::size_t remaining = data_a.size();

        xmcu::bit::flag::set(&(this->cr2),
                             I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RD_WRN,
                             (address_a & I2C_CR2_SADD) | data_length_mask(remaining) | I2C_CR2_START);

        while (remaining != 0u && false == xmcu::bit::flag::is(this->isr, I2C_ISR_NACKF | I2C_ISR_ARLO | I2C_ISR_BERR | I2C_ISR_OVR) &&
               std::chrono::steady_clock::now() < end_time_point)
        {
            const std::size_t i = data_a.size() - remaining;
            if (true == xmcu::bit::flag::is(this->isr, I2C_ISR_TXE))
            {
                this->txdr = data_a[i];
                remaining--;
            }

            if (i > 255u && xmcu::bit::flag::is(this->cr2, I2C_CR2_RELOAD))
            {
                xmcu::bit::flag::set(&(this->cr2),
                                     I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RD_WRN,
                                     (address_a & I2C_CR2_SADD) | data_length_mask(remaining) | I2C_CR2_START);
            }
        }

        xmcu::bit::wait_for::all_set(this->isr, I2C_ISR_STOPF);

        const Error err = static_cast<Error>(this->isr & (I2C_ISR_NACKF | I2C_ISR_ARLO | I2C_ISR_BERR | I2C_ISR_OVR));

        if (Error::none != err)
        {
            xmcu::bit::flag::set(&(this->icr), I2C_ICR_NACKCF | I2C_ICR_ARLOCF | I2C_ICR_BERRCF | I2C_ICR_OVRCF);
        }

        return { data_a.size() - remaining, err };
    }

    std::size_t receive(std::uint16_t address_a, std::span<std::uint8_t> data_a) const;
    std::size_t receive(std::uint16_t address_a, std::span<std::uint8_t> data_a, std::chrono::milliseconds timeout_a) const;

private:
    std::uint32_t data_length_mask(std::size_t length_a)
    {
        return length_a <= 255u ? ((length_a << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES_Msk) | I2C_CR2_AUTOEND :
                                  0x1FF0000u /*255u << I2C_CR2_NBYTES_Pos | I2C_CR2_RELOAD*/;
    }
};
template<> class i2c::Transceiver<api::traits::sync, i2c::slave> : private ll::i2c::Peripheral
{
};

template<> class i2c::Transceiver<api::traits::async, i2c::master> : private ll::i2c::Peripheral
{
};
template<> class i2c::Transceiver<api::traits::async, i2c::slave> : private ll::i2c::Peripheral
{
};

template<> inline i2c::Transceiver<api::traits::sync, i2c::master>*
i2c::Peripheral<i2c::master>::view<i2c::Transceiver<api::traits::sync, i2c::master>>() const
{
    const std::uintptr_t base_address = reinterpret_cast<std::uintptr_t>(this);
    return reinterpret_cast<Transceiver<api::traits::sync, i2c::master>*>(base_address);
}
template<> inline i2c::Transceiver<api::traits::sync, i2c::slave>*
i2c::Peripheral<i2c::slave>::view<i2c::Transceiver<api::traits::sync, i2c::slave>>() const
{
    const std::uintptr_t base_address = reinterpret_cast<std::uintptr_t>(this);
    return reinterpret_cast<Transceiver<api::traits::sync, i2c::slave>*>(base_address);
}

template<> inline i2c::Transceiver<api::traits::async, i2c::master>*
i2c::Peripheral<i2c::master>::view<i2c::Transceiver<api::traits::async, i2c::master>>() const
{
    const std::uintptr_t base_address = reinterpret_cast<std::uintptr_t>(this);
    return reinterpret_cast<Transceiver<api::traits::async, i2c::master>*>(base_address);
}
template<> inline i2c::Transceiver<api::traits::async, i2c::slave>*
i2c::Peripheral<i2c::slave>::view<i2c::Transceiver<api::traits::async, i2c::slave>>() const
{
    const std::uintptr_t base_address = reinterpret_cast<std::uintptr_t>(this);
    return reinterpret_cast<Transceiver<api::traits::async, i2c::slave>*>(base_address);
}
} // namespace soc::st::arm::m0::u0::rm0503::peripherals