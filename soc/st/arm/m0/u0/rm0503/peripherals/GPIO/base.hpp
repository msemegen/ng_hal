#pragma once

/*
 *	Name: base.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>

// xmcu
#include <xmcu/non_constructible.hpp>

namespace soc::st::arm::m0::u0::rm0503::peripherals {
#if XMCU_SOC_STM32_MODEL == stm32l0u083rct6u
#define XMCU_GPIOA_PRESENT
#define XMCU_GPIOB_PRESENT
#define XMCU_GPIOC_PRESENT
#define XMCU_GPIOD_PRESENT
#define XMCU_GPIOF_PRESENT

struct gpio_base : private xmcu::non_constructible
{
public:
    enum class A : std::uint8_t
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
    enum class B : std::uint8_t
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
    enum class C : std::uint8_t
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
    enum class D : std::uint8_t
    {
        _2 = 2u
    };
    enum class F : std::uint8_t
    {
        _0,
        _1,
        _2
    };

public:
    friend constexpr bool operator==(gpio_base::A, gpio_base::B)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::A, gpio_base::C)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::A, gpio_base::D)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::B, gpio_base::A)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::B, gpio_base::C)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::B, gpio_base::D)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::C, gpio_base::A)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::C, gpio_base::B)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::C, gpio_base::D)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::D, gpio_base::A)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::D, gpio_base::B)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::D, gpio_base::C)
    {
        return false;
    }
};
#endif
} // namespace soc::st::arm::m0::u0::rm0503::peripherals