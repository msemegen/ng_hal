#pragma once

/*
 *	Name: hsi16.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cassert>

// CMSIS
#include <stm32u0xx.h>

// xmcu
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>

namespace soc::st::arm::m0::u0::rm0503::oscillators {
namespace ll {
struct hsi16
{
    // ?
};
} // namespace ll

struct hsi16 : private xmcu::non_constructible
{
    struct Descriptor
    {
        enum class Start_from_stop : std::uint32_t
        {
            disable = 0x0u,
            enable = RCC_CR_HSIASFS
        };
        enum class Power : std::uint32_t
        {
            only_in_run = 0x0u,
            always = RCC_CR_HSIKERON
        };

        Start_from_stop start_from_stop;
        Power power;

        std::uint8_t trimm = 0x0u;
        std::uint8_t calibration = 0x0u;
    };

    static void set_descriptor(const Descriptor& descriptor_a)
    {
        xmcu::bit::flag::set(&(RCC->CR), RCC_CR_HSIASFS, static_cast<std::uint32_t>(descriptor_a.start_from_stop));
        xmcu::bit::flag::set(&(RCC->CR), RCC_CR_HSIKERON, static_cast<std::uint32_t>(descriptor_a.power));
    }
    [[nodiscard]] static Descriptor get_descriptor()
    {
        return {};
    }

    static void enable()
    {
        assert(false == is_enabled());

        xmcu::bit::flag::set(&(RCC->CR), RCC_CR_HSION);
    }
    static void disable()
    {
        assert(true == is_enabled());

        xmcu::bit::flag::clear(&(RCC->CR), RCC_CR_HSION);
    }

    [[nodiscard]] static bool is_ready()
    {
        return xmcu::bit::flag::is(RCC->CR, RCC_CR_HSIRDY);
    }

    [[nodiscard]] static bool is_enabled()
    {
        return xmcu::bit::flag::is(RCC->CR, RCC_CR_HSION);
    }

    [[nodiscard]] static std::uint32_t get_frequency_Hz()
    {
        return 16'000'000u;
    }
};
} // namespace soc::st::arm::m0::u0::rm0503::oscillators