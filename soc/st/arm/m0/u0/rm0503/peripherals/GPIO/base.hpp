#pragma once

/*
 *	Name: base.hpp
 *
 *   Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *   Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>

namespace soc::st::arm::m0::u0::rm0503::peripherals {
#if XMCU_SOC_STM32_MODEL == stm32l0u083rct6u
#define XMCU_GPIOA_PRESENT
#define XMCU_GPIOB_PRESENT
#define XMCU_GPIOC_PRESENT
#define XMCU_GPIOD_PRESENT

struct gpio_base
{
protected:
    enum class a : std::uint8_t
    {
        _0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        _11,
        _12,
        _13,
        _14,
        _15
    };
    enum class b : std::uint8_t
    {
        _0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        _11,
        _12,
        _13,
        _14,
        _15
    };
    enum class c : std::uint8_t
    {
        _0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        _11,
        _12,
        _13,
        _14,
        _15
    };
    enum class d : std::uint8_t
    {
        _2 = 2u
    };

public:
    friend constexpr bool operator==(gpio_base::a, gpio_base::b)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::a, gpio_base::c)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::a, gpio_base::d)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::b, gpio_base::a)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::b, gpio_base::c)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::b, gpio_base::d)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::c, gpio_base::a)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::c, gpio_base::b)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::c, gpio_base::d)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::d, gpio_base::a)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::d, gpio_base::b)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::d, gpio_base::c)
    {
        return false;
    }
};
#endif
} // namespace soc::st::arm::m0::u0::rm0503::peripherals