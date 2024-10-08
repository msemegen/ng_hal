#pragma once

/*
 *	Name: hse.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details. * 
 */

// clang-format off
// xmcu
#include <xmcu/macros.hpp>
// soc
#include DECORATE_INCLUDE_PATH(soc/XMCU_SOC_VENDOR/XMCU_SOC_ARCH/XMCU_SOC_ARCH_CORE_FAMILY/XMCU_SOC_VENDOR_FAMILY/XMCU_SOC_VENDOR_FAMILY_RM/oscillators/msi.hpp)
// clang-format on

namespace xmcu::hal::oscillators {
#if !defined XMCU_LL_ONLY
using msi =
    soc::XMCU_SOC_VENDOR::XMCU_SOC_ARCH::XMCU_SOC_ARCH_CORE_FAMILY::XMCU_SOC_VENDOR_FAMILY::XMCU_SOC_VENDOR_FAMILY_RM::oscillators::msi;
#endif

#if defined XMCU_LL_ONLY
inline
#endif
    namespace ll {
using msi =
    soc::XMCU_SOC_VENDOR::XMCU_SOC_ARCH::XMCU_SOC_ARCH_CORE_FAMILY::XMCU_SOC_VENDOR_FAMILY::XMCU_SOC_VENDOR_FAMILY_RM::oscillators::ll::msi;
} // namespace ll
} // namespace xmcu::hal::oscillators