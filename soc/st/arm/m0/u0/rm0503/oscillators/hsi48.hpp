#pragma once

/*
 *	Name: hsi48.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// xmcu
#include <xmcu/non_constructible.hpp>

namespace soc::st::arm::m0::u0::rm0503::oscillators {
namespace ll {
struct hsi48
{
    // ?
};
} // namespace ll

struct hsi48 : private xmcu::non_constructible
{
};
} // namespace soc::st::arm::m0::u0::rm0503::oscillators