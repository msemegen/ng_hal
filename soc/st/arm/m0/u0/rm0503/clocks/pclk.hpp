#pragma once

/*
 *	Name: pclk.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>

// CMSIS
#include <stm32u0xx.h>

// xmcu
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>

// soc
#include <soc/st/arm/m0/u0/rm0503/clocks/base.hpp>
#include <soc/st/arm/m0/u0/rm0503/clocks/hclk.hpp>

namespace soc::st::arm::m0::u0::rm0503::clocks {
namespace ll {
struct pclk : private xmcu::non_constructible
{
    // ?
};
} // namespace ll

struct pclk : private xmcu::non_constructible
{
    struct Descriptor
    {
        enum class Prescaler : std::uint32_t
        {
            _1 = RCC_CFGR_PPRE_0 | RCC_CFGR_PPRE_1 | RCC_CFGR_PPRE_2,
            _2 = RCC_CFGR_PPRE_2,
            _4 = RCC_CFGR_PPRE_0 | RCC_CFGR_PPRE_2,
            _8 = RCC_CFGR_PPRE_1 | RCC_CFGR_PPRE_2,
            _16 = RCC_CFGR_PPRE_0 | RCC_CFGR_PPRE_1 | RCC_CFGR_PPRE_2,
        };

        Prescaler prescaler;
    };

    static void set_descriptor(Descriptor descriptor_a)
    {
        xmcu::bit::flag::set(&(RCC->CFGR), RCC_CFGR_PPRE, static_cast<std::uint32_t>(descriptor_a.prescaler));
    }

    [[nodiscard]] static Descriptor get_descriptor()
    {
        return Descriptor { .prescaler = static_cast<Descriptor::Prescaler>(xmcu::bit::flag::get(RCC->CFGR, RCC_CFGR_PPRE)) };
    }

    [[nodiscard]] static std::uint32_t get_frequency_Hz()
    {
        const std::uint32_t lut_pos = (xmcu::bit::flag::get(RCC->CFGR, RCC_CFGR_PPRE) >> RCC_CFGR_PPRE_Pos) -
                                      (static_cast<std::uint32_t>(Descriptor::Prescaler::_1) >> RCC_CFGR_PPRE_Pos);
        return hclk::get_frequency_Hz() >> details::shift_lut[lut_pos];
    }
};
} // namespace soc::st::arm::m0::u0::rm0503::clocks