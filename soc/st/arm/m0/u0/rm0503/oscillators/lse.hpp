#pragma once

/*
 *	Name: lse.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// CMSIS
#include <stm32u0xx.h>

// xmcu
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>

// soc
#include <soc/st/arm/m0/u0/rm0503/peripherals/GPIO/gpio.hpp>

namespace soc::st::arm::m0::u0::rm0503::oscillators {
namespace deatils {
template<auto... pins_t> struct LSE_pins
{
    static constexpr bool is(auto value_a)
    {
        return ((value_a == pins_t) || ...);
    }
};

#if XMCU_SOC_STM32_MODEL == stm32l0u083rct6u
constexpr LSE_pins<peripherals::gpio::C::Pin::_14> osc_in;
constexpr LSE_pins<peripherals::gpio::C::Pin::_15> osc_out;
#endif
} // namespace deatils
} // namespace soc::st::arm::m0::u0::rm0503::oscillators

namespace soc::st::arm::m0::u0::rm0503::oscillators {
namespace ll {
struct lse
{
};
} // namespace ll

struct lse : private xmcu::non_constructible
{
    struct traits : private xmcu::non_constructible
    {
    private:
        enum class Source : std::uint32_t
        {
            clock,
            xtal
        };

        friend lse;

    public:
        enum class Drive : std::uint32_t
        {
            low = 0x0u,
            medium_low = RCC_BDCR_LSEDRV_0,
            medium_high = RCC_BDCR_LSEDRV_1,
            high = RCC_BDCR_LSEDRV_0 | RCC_BDCR_LSEDRV_1
        };
        struct clock
        {
            constexpr static Source type = Source::clock;
        };
        template<auto osc_in_pin_t, auto osc_out_pin_t, Drive drive_t> struct xtal
        {
            constexpr static Source type = Source::xtal;

            constexpr static auto osc_in_pin = osc_in_pin_t;
            constexpr static auto osc_out_pin = osc_out_pin_t;
            constexpr static auto drive = drive_t;
        };
    };

    template<typename trait_t> void set_traits()
    {
        if constexpr (traits::Source::xtal == trait_t::type)
        {
            static_assert(true == details::osc_in.is(trait_t::osc_in_pin));
            static_assert(true == details::osc_out.is(trait_t::osc_out_pin));

            assert(false == lse::is_enabled());
            xmcu::bit::flag::clear(&(RCC->BDCR), RCC_BDCR_LSEBYP | trait_t::drive);
            xmcu::bit::flag::set(&(RCC->BDCR), static_cast<std::uint32_t>(trait_t::drive));
        }
        else
        {
            assert(false == lse::is_enabled());
            xmcu::bit::flag::clear(&(RCC->BDCR), RCC_BDCR_LSEBYP);
        }
    }

    static void enable()
    {
        xmcu::bit::flag::set(&(RCC->BDCR), RCC_BDCR_LSEON | RCC_BDCR_LSESYSEN);
    }
    static void disable()
    {
        xmcu::bit::flag::clear(&(RCC->BDCR), RCC_BDCR_LSEON | RCC_BDCR_LSESYSEN);
    }

    [[nodiscard]] static bool is_enabled()
    {
        return xmcu::bit::flag::is(RCC->BDCR, RCC_BDCR_LSEON);
    }

    [[nodiscard]] static bool is_ready()
    {
        return xmcu::bit::flag::is(RCC->BDCR, RCC_BDCR_LSERDY);
    }

    [[nodiscard]] static std::uint32_t get_frequency_Hz()
    {
        return 32768u;
    }
};
} // namespace soc::st::arm::m0::u0::rm0503::oscillators