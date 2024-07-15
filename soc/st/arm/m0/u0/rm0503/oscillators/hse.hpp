#pragma once

/*
 *	Name: hse.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cassert>

// CMSIS
#include <stm32u0xx.h>

// xmcu
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>

// soc
#include <soc/st/arm/m0/u0/rm0503/peripherals/GPIO/gpio.hpp>

namespace soc::st::arm::m0::u0::rm0503::oscillators {
namespace details {
template<auto... pins_t> struct HSE_pins
{
    static constexpr bool is(auto value_a)
    {
        return ((value_a == pins_t) || ...);
    }
};
#if XMCU_SOC_STM32_MODEL == stm32l0u083rct6u
HSE_pins<peripherals::gpio::F::Pin::_0> osc_in;
HSE_pins<peripherals::gpio::F::Pin::_1> osc_out;
#endif
} // namespace details

namespace ll {
struct hse : private xmcu::non_constructible
{
};
} // namespace ll

struct hse : private xmcu::non_constructible
{
    struct traits : private xmcu::non_constructible
    {
    private:
        enum class Source : std::uint32_t
        {
            clock,
            xtal
        };

        friend hse;

    public:
        struct clock
        {
            static constexpr Source type = Source::clock;
        };
        template<auto osc_in_pin_t, auto osc_out_pin_t> struct xtal
        {
            static constexpr Source type = Source::xtal;

            constexpr static auto osc_in_pin = osc_in_pin_t;
            constexpr static auto osc_out_pin = osc_out_pin_t;
        };
    };

    template<typename Source_t> static void set_traits()
    {
        if constexpr (traits::Source::xtal == Source_t::type)
        {
            static_assert(true == details::osc_in.is(Source_t::osc_in_pin));
            static_assert(true == details::osc_out.is(Source_t::osc_out_pin));

            xmcu::bit::flag::clear(&(RCC->CR), RCC_CR_HSEBYP);
        }
        else
        {
            xmcu::bit::flag::set(&(RCC->CR), RCC_CR_HSEBYP);
        }
    }

    static void enable(std::uint32_t frequency_Hz_a)
    {
        assert(false == is_enabled());

        xmcu::bit::flag::set(&(RCC->CR), RCC_CR_HSEON);
        frequency_Hz = frequency_Hz_a;
    }
    static void disable()
    {
        assert(true == is_enabled());

        xmcu::bit::flag::clear(&(RCC->CR), RCC_CR_HSEON);
    }

    static bool is_ready()
    {
        return xmcu::bit::flag::is(RCC->CR, RCC_CR_HSERDY);
    }

    static bool is_enabled()
    {
        return xmcu::bit::flag::is(RCC->CR, RCC_CR_HSEON);
    }

    static std::uint32_t get_frequency_Hz()
    {
        return frequency_Hz;
    }

private:
    inline static std::uint32_t frequency_Hz = 0u;
};
} // namespace soc::st::arm::m0::u0::rm0503::oscillators