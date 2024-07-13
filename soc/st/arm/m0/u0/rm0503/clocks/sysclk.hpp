#pragma once

/*
 *	Name: sysclk.hpp
 *
 *   Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *   Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cassert>

// xmcu
#include <xmcu/bit_flag.hpp>
#include <xmcu/non_constructible.hpp>

// soc
#include <soc/st/arm/m0/u0/rm0503/oscillators/hsi16.hpp>
#include <soc/st/arm/m0/u0/rm0503/oscillators/msi.hpp>

namespace soc::st::arm::m0::u0::rm0503::clocks {
namespace ll {
struct sysclk
{
    // ?
};
} // namespace ll

struct sysclk : private xmcu::non_constructible
{
    template<typename Oscillator_t> static void set_source() = delete;
    template<typename Oscillator_t> static bool is_source() = delete;

    static std::uint32_t get_frequency_Hz();
};

template<> inline void sysclk::set_source<soc::st::arm::m0::u0::rm0503::oscillators::hsi16>()
{
    xmcu::bit_flag::set(&(RCC->CFGR), RCC_CFGR_SW, RCC_CFGR_SW_0);
}
template<> inline bool sysclk::is_source<soc::st::arm::m0::u0::rm0503::oscillators::hsi16>()
{
    return xmcu::bit_flag::is(RCC->CFGR, RCC_CFGR_SWS_0);
}

template<> inline void sysclk::set_source<soc::st::arm::m0::u0::rm0503::oscillators::msi>()
{
    xmcu::bit_flag::clear(&(RCC->CFGR), RCC_CFGR_SW);
}
template<> inline bool sysclk::is_source<soc::st::arm::m0::u0::rm0503::oscillators::msi>()
{
    return 0x0u == xmcu::bit_flag::get(RCC->CFGR, RCC_CFGR_SWS);
}

inline std::uint32_t sysclk::get_frequency_Hz()
{
    if (true == sysclk::is_source<soc::st::arm::m0::u0::rm0503::oscillators::hsi16>())
    {
        return soc::st::arm::m0::u0::rm0503::oscillators::hsi16::get_frequency_Hz();
    }
    if (true == sysclk::is_source<soc::st::arm::m0::u0::rm0503::oscillators::msi>())
    {
        return soc::st::arm::m0::u0::rm0503::oscillators::msi::get_frequency_Hz();
    }

    assert(false);

    return 0;
}

} // namespace soc::st::arm::m0::u0::rm0503::clocks