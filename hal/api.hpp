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
#include DECORATE_INCLUDE_PATH(soc/st/arm/api.hpp)
// clang-format on

namespace hal {
using api = soc::st::arm::api;
} // namespace hal