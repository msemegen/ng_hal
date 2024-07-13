#pragma once

/*
 *	Name: api.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// clang-format off
// xmcu
#include <xmcu/macros.hpp>
// soc
#include DECORATE_INCLUDE_PATH(soc/st/arm/api.hpp)
// clang-format on

namespace xmcu::hal {
using api = soc::st::arm::api;
} // namespace xmcu::hal