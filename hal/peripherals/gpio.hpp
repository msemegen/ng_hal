#pragma once

/*
 *	Name: gpio.hpp
 *
 *   Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *   Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// xmcu
// clang-format off
#include <soc/macros.hpp>
#include DECORATE_INCLUDE_PATH(soc/XMCU_SOC_VENDOR/XMCU_SOC_ARCH/XMCU_SOC_ARCH_CORE_FAMILY/XMCU_SOC_VENDOR_FAMILY/XMCU_SOC_VENDOR_FAMILY_RM/peripherals/GPIO/gpio.hpp)
// clang-format on

namespace hal::peripherals {
#if !defined XMCU_LL_ONLY
using gpio = soc::XMCU_SOC_VENDOR::XMCU_SOC_ARCH::XMCU_SOC_ARCH_CORE_FAMILY::XMCU_SOC_VENDOR_FAMILY::
    XMCU_SOC_VENDOR_FAMILY_RM::peripherals::gpio;
#endif

#if defined XMCU_LL_ONLY
inline
#endif
    namespace ll {
// using gpio = soc::XMCU_SOC_VENDOR::XMCU_SOC_ARCH::XMCU_SOC_ARCH_CORE_FAMILY::XMCU_SOC_VENDOR_FAMILY::
//     XMCU_SOC_VENDOR_FAMILY_RM::peripherals::ll::gpio;
} // namespace ll
} // namespace hal::peripherals