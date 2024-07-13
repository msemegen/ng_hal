#pragma once

/*
 *	Name: IRQ_priority.hpp
 *
 *   Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *   Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// clang-format off
// xmcu
#include <xmcu/macros.hpp>
// soc
#include DECORATE_INCLUDE_PATH(soc/XMCU_SOC_VENDOR/XMCU_SOC_ARCH/IRQ_priority.hpp)
// clang-format on

namespace xmcu::hal {
using IRQ_priority = soc::XMCU_SOC_VENDOR::XMCU_SOC_ARCH::IRQ_priority;
} // namespace xmcu::hal