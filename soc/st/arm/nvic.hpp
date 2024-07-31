#pragma once

/*
 *	Name: nvic.cpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// xmcu
#include <xmcu/non_constructible.hpp>

namespace soc::st::arm {
class nvic : xmcu::non_constructible
{
};
} // namespace soc::st::arm