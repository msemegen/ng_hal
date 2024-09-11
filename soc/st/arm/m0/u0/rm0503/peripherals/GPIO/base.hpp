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
    enum class A : std::uint32_t
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
    enum class B : std::uint32_t
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
    enum class C : std::uint32_t
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
    enum class D : std::uint32_t
    {
        _2 = 2u
    };
    enum class F : std::uint32_t
    {
        _0,
        _1,
        _2
    };

    enum class Moder_flag : std::uint32_t
    {
        input = 0x0u,
        output = 0x1u,
        af = 0x2u,
        analog = 0x3u
    };
    enum class Otyper_flag : std::uint32_t
    {
        push_pull = 0x0u,
        open_drain = 0x1u,
    };
    enum class Ospeedr_flag : std::uint32_t
    {
        low = 0x0u,
        medium = 0x1u,
        high = 0x2u,
        ultra = 0x3u
    };
    enum class Pupdr_flag : std::uint32_t
    {
        none = 0x0u,
        pull_up = 0x1u,
        pull_down = 0x2u,
    };
    enum class Idr_flag : std::uint32_t
    {
        low,
        high
    };
    enum class Odr_flag : std::uint32_t
    {
        low,
        high
    };
};

constexpr bool operator==(gpio_base::A, gpio_base::B)
{
    return false;
}
constexpr bool operator==(gpio_base::A, gpio_base::C)
{
    return false;
}
constexpr bool operator==(gpio_base::A, gpio_base::D)
{
    return false;
}

constexpr bool operator==(gpio_base::B, gpio_base::A)
{
    return false;
}
constexpr bool operator==(gpio_base::B, gpio_base::C)
{
    return false;
}
constexpr bool operator==(gpio_base::B, gpio_base::D)
{
    return false;
}

constexpr bool operator==(gpio_base::C, gpio_base::A)
{
    return false;
}
constexpr bool operator==(gpio_base::C, gpio_base::B)
{
    return false;
}
constexpr bool operator==(gpio_base::C, gpio_base::D)
{
    return false;
}

constexpr bool operator==(gpio_base::D, gpio_base::A)
{
    return false;
}
constexpr bool operator==(gpio_base::D, gpio_base::B)
{
    return false;
}
constexpr bool operator==(gpio_base::D, gpio_base::C)
{
    return false;
}
#endif
} // namespace soc::st::arm::m0::u0::rm0503::peripherals