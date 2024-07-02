#pragma once

/*
 *	Name: usart.hpp
 *
 *   Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *   Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// xmcu
// clang-format off
#include <soc/macros.hpp>
#include DECORATE_INCLUDE_PATH(soc/XMCU_SOC_VENDOR/XMCU_SOC_ARCH/XMCU_SOC_ARCH_CORE_FAMILY/XMCU_SOC_VENDOR_FAMILY/XMCU_SOC_VENDOR_FAMILY_RM/peripherals/USART/usart.hpp)
// clang-format on

namespace hal::peripherals {
#if !defined XMCU_LL_ONLY
using usart = soc::XMCU_SOC_VENDOR::XMCU_SOC_ARCH::XMCU_SOC_ARCH_CORE_FAMILY::XMCU_SOC_VENDOR_FAMILY::
    XMCU_SOC_VENDOR_FAMILY_RM::peripherals::usart;
#endif

#if defined XMCU_LL_ONLY
inline
#endif
    namespace ll {
using usart = soc::XMCU_SOC_VENDOR::XMCU_SOC_ARCH::XMCU_SOC_ARCH_CORE_FAMILY::XMCU_SOC_VENDOR_FAMILY::
    XMCU_SOC_VENDOR_FAMILY_RM::peripherals::ll::usart;
} // namespace ll
} // namespace hal::peripherals