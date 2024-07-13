#pragma once

/*
 *	Name: hclk.hpp
 *
 *   Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *   Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// clang-format off
// xmcu
#include <xmcu/macros.hpp>
// soc
#include DECORATE_INCLUDE_PATH(soc/XMCU_SOC_VENDOR/XMCU_SOC_ARCH/XMCU_SOC_ARCH_CORE_FAMILY/XMCU_SOC_VENDOR_FAMILY/XMCU_SOC_VENDOR_FAMILY_RM/clocks/sysclk.hpp)
// clang-format on

namespace xmcu::hal::clocks {
#if !defined XMCU_LL_ONLY
using sysclk =
    soc::XMCU_SOC_VENDOR::XMCU_SOC_ARCH::XMCU_SOC_ARCH_CORE_FAMILY::XMCU_SOC_VENDOR_FAMILY::XMCU_SOC_VENDOR_FAMILY_RM::clocks::sysclk;
#endif

#if defined XMCU_LL_ONLY
inline
#endif
    namespace ll {
using sysclk =
    soc::XMCU_SOC_VENDOR::XMCU_SOC_ARCH::XMCU_SOC_ARCH_CORE_FAMILY::XMCU_SOC_VENDOR_FAMILY::XMCU_SOC_VENDOR_FAMILY_RM::clocks::ll::sysclk;
} // namespace ll
} // namespace xmcu::hal::clocks