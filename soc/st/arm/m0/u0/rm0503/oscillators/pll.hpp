#pragma once

/*
 *	Name: pll.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cassert>

// CMSIS
#include <stm32u0xx.h>

// xmcu
#include <xmcu/Limited.hpp>
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>

// soc
#include <soc/st/arm/m0/u0/rm0503/oscillators/hse.hpp>
#include <soc/st/arm/m0/u0/rm0503/oscillators/hsi16.hpp>
#include <soc/st/arm/m0/u0/rm0503/oscillators/msi.hpp>

namespace soc::st::arm::m0::u0::rm0503::oscillators {
namespace ll {
struct pll : private xmcu::non_constructible
{
    // ?
};
} // namespace ll

struct pll : private xmcu::non_constructible
{
    struct traits : private xmcu::non_constructible
    {
        template<typename Oscillator> struct source : private xmcu::non_constructible
        {
        };
    };

    struct Descriptor
    {
        xmcu::Limited<std::uint32_t, 1u, 8u> m;
        xmcu::Limited<std::uint32_t, 4u, 127u> n;
    };

    struct P : private xmcu::non_copyable
    {
        struct Descriptor
        {
            xmcu::Limited<std::uint32_t, 2u, 32u> divider;
        };

        void set_descriptor(Descriptor descriptor_a) {}

        void enable();
        void disable();
    };
    struct R : private xmcu::non_copyable
    {
        struct Descriptor
        {
            xmcu::Limited<std::uint32_t, 2u, 8u> divider;
        };

        void set_descriptor(Descriptor descriptor_a) {}

        void enable();
        void disable();
    };
    struct Q : private xmcu::non_copyable
    {
        struct Descriptor
        {
            xmcu::Limited<std::uint32_t, 2u, 8u> divider;
        };
        void set_descriptor(Descriptor descriptor_a) {}
    };

    static P p;
    static Q q;
    static R r;

    template<typename trait> void set_traits() = delete;
    template<typename trait> [[nodiscard]] bool is_trait() = delete;

    static void set_descriptor(Descriptor descriptor_a)
    {
        xmcu::bit::flag::set(&(RCC->PLLCFGR), RCC_PLLCFGR_PLLM, (descriptor_a.m - 1u) << RCC_PLLCFGR_PLLM_Pos);
        xmcu::bit::flag::set(&(RCC->PLLCFGR), RCC_PLLCFGR_PLLN, (descriptor_a.n) << RCC_PLLCFGR_PLLN_Pos);
    }

    static void enable()
    {
        xmcu::bit::flag::set(&(RCC->PLLCFGR), RCC_PLLCFGR_PLLPEN);
    }
    static void disble()
    {
        xmcu::bit::flag::clear(&(RCC->PLLCFGR), RCC_PLLCFGR_PLLPEN);
    }

    [[nodiscard]] static bool is_enabled()
    {
        return xmcu::bit::flag::is(RCC->PLLCFGR, RCC_PLLCFGR_PLLPEN);
    }
    [[nodiscard]] static bool is_ready()
    {
        return xmcu::bit::flag::is(RCC->CR, RCC_CR_PLLRDY);
    }
};
template<> inline void pll::set_traits<pll::traits::source<soc::st::arm::m0::u0::rm0503::oscillators::hsi16>>()
{
    assert(false == pll::is_enabled());
    xmcu::bit::flag::set(&(RCC->PLLCFGR), RCC_PLLCFGR_PLLSRC, RCC_PLLCFGR_PLLSRC_1);
}
template<> [[nodiscard]] inline bool pll::is_trait<pll::traits::source<soc::st::arm::m0::u0::rm0503::oscillators::hsi16>>()
{
    return false == xmcu::bit::flag::is(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_0) &&
           true == xmcu::bit::flag::is(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_1);
}

template<> inline void pll::set_traits<pll::traits::source<soc::st::arm::m0::u0::rm0503::oscillators::msi>>()
{
    assert(false == pll::is_enabled());
    xmcu::bit::flag::set(&(RCC->PLLCFGR), RCC_PLLCFGR_PLLSRC, RCC_PLLCFGR_PLLSRC_0);
}
template<> [[nodiscard]] inline bool pll::is_trait<pll::traits::source<soc::st::arm::m0::u0::rm0503::oscillators::msi>>()
{
    return true == xmcu::bit::flag::is(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_0) &&
           false == xmcu::bit::flag::is(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_1);
}
template<> inline void pll::set_traits<pll::traits::source<soc::st::arm::m0::u0::rm0503::oscillators::hse>>()
{
    assert(false == pll::is_enabled());
    xmcu::bit::flag::set(&(RCC->PLLCFGR), RCC_PLLCFGR_PLLSRC, RCC_PLLCFGR_PLLSRC_0 | RCC_PLLCFGR_PLLSRC_1);
}
template<> [[nodiscard]] inline bool pll::is_trait<pll::traits::source<soc::st::arm::m0::u0::rm0503::oscillators::hse>>()
{
    return true == xmcu::bit::flag::is(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_0) &&
           true == xmcu::bit::flag::is(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_1);
}
} // namespace soc::st::arm::m0::u0::rm0503::oscillators