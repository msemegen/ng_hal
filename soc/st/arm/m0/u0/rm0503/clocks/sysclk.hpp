#pragma once

/*
 *	Name: sysclk.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cassert>

// xmcu
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>

// soc
#include <soc/st/arm/m0/u0/rm0503/oscillators/hsi16.hpp>
#include <soc/st/arm/m0/u0/rm0503/oscillators/msi.hpp>
#include <soc/st/arm/m0/u0/rm0503/oscillators/pll.hpp>

namespace soc::st::arm::m0::u0::rm0503::clocks {
namespace ll {
struct sysclk
{
    // ?
};
} // namespace ll

struct sysclk : private xmcu::non_constructible
{
    struct traits
    {
        template<typename Oscillator> struct source : private xmcu::non_constructible
        {
        };
    };
    template<typename trait> static void set_traits() = delete;
    template<typename triat> static bool is_trait() = delete;

    static std::uint32_t get_frequency_Hz();
};

template<> inline void sysclk::set_traits<sysclk::traits::source<soc::st::arm::m0::u0::rm0503::oscillators::hsi16>>()
{
    xmcu::bit::flag::set(&(RCC->CFGR), RCC_CFGR_SW, RCC_CFGR_SW_0);
}
template<> inline bool sysclk::is_trait<sysclk::traits::source<soc::st::arm::m0::u0::rm0503::oscillators::hsi16>>()
{
    return xmcu::bit::flag::is(RCC->CFGR, RCC_CFGR_SWS_0);
}

template<> inline void sysclk::set_traits<sysclk::traits::source<soc::st::arm::m0::u0::rm0503::oscillators::msi>>()
{
    xmcu::bit::flag::clear(&(RCC->CFGR), RCC_CFGR_SW);
}
template<> inline bool sysclk::is_trait<sysclk::traits::source<soc::st::arm::m0::u0::rm0503::oscillators::msi>>()
{
    return 0x0u == xmcu::bit::flag::get(RCC->CFGR, RCC_CFGR_SWS);
}

inline std::uint32_t sysclk::get_frequency_Hz()
{
    if (true == sysclk::is_trait<sysclk::traits::source<soc::st::arm::m0::u0::rm0503::oscillators::hsi16>>())
    {
        return soc::st::arm::m0::u0::rm0503::oscillators::hsi16::get_frequency_Hz();
    }
    if (true == sysclk::is_trait<sysclk::traits::source<soc::st::arm::m0::u0::rm0503::oscillators::msi>>())
    {
        return soc::st::arm::m0::u0::rm0503::oscillators::msi::get_frequency_Hz();
    }

    assert(false);

    return 0;
}

} // namespace soc::st::arm::m0::u0::rm0503::clocks