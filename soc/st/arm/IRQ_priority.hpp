#pragma once

/*
 *	Name: IRQ_priority.hpp
 *
 *   Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *   Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>

namespace soc::st::arm {
struct IRQ_priority
{
    std::uint32_t preempt_priority = 0;
    std::uint32_t sub_priority = 0;
};
} // namespace soc::st::arm