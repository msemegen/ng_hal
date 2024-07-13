#pragma once

/*
 *	Name: stdglue.hpp
 *
 *   Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *   Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// clang-format off
// xmcu
#include <xmcu/macros.hpp>
// soc
#include DECORATE_INCLUDE_PATH(soc/XMCU_SOC_VENDOR/XMCU_SOC_ARCH/stdglue.hpp)
// clang-format on

namespace xmcu::hal {
using stdglue = soc::XMCU_SOC_VENDOR::XMCU_SOC_ARCH::stdglue;
} // namespace xmcu::hal