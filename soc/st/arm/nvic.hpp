#pragma once

/*
 *	Name: nvic.cpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>

// clang-format off
// xmcu
#include <xmcu/macros.hpp>
// CMSIS
#include DECORATE_INCLUDE_PATH(CMSIS_SOC_FILE)
// clang-format on

// xmcu
#include <xmcu/Scoped_guard.hpp>
#include <xmcu/non_constructible.hpp>

namespace soc::st::arm {
class nvic : xmcu::non_constructible
{
public:
    struct Descriptor
    {
        enum class Grouping : std::uint32_t
        {
            _0 = 0x7,
            _1 = 0x6,
            _2 = 0x5,
            _3 = 0x4,
            _4 = 0x3,
        };

        Grouping grouping;
#if XMCU_SOC_STM32_FAMILY != m0 && XMCU_SOC_STM32_FAMILY != m23
        std::uint32_t lowest_avaliable_priority = 0x0u;
#endif
    };

    static void set_descriptor(const Descriptor& descriptor_a)
    {
        NVIC_SetPriorityGrouping(static_cast<std::uint32_t>(descriptor_a.grouping));
#if XMCU_SOC_STM32_FAMILY != m0 && XMCU_SOC_STM32_FAMILY != m23
        __set_BASEPRI(descriptor_a.lowest_avaliable_priority << (0x8u - __NVIC_PRIO_BITS));
#endif
    }

    static Descriptor get_descriptor()
    {
        return {};
    }

    static void enable()
    {
        __enable_irq();
    }
    static void disable()
    {
        __disable_irq();
    }

    static bool is_enabled()
    {
        return 0x0u == __get_PRIMASK();
    }
};
} // namespace soc::st::arm

namespace xmcu {
template<> class Scoped_guard<soc::st::arm::nvic>
{
public:
    Scoped_guard()
        : start_state(soc::st::arm::nvic::is_enabled())
    {
        soc::st::arm::nvic::disable();
    }

    ~Scoped_guard()
    {
        if (true == this->start_state)
        {
            soc::st::arm::nvic::enable();
        }
    }

private:
    bool start_state;
};
} // namespace xmcu