#pragma once

/*
 *	Name: hsi48.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>
#include <chrono>

// CMSIS
#include <stm32u0xx.h>

// xmcu
#include <xmcu/bit.hpp>
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
    static void enable(std::chrono::milliseconds timeout_a)
    {
        xmcu::bit::flag::set(&(RCC->CRRCR), RCC_CRRCR_HSI48ON);
        xmcu::bit::wait_for::all_set(RCC->CRRCR, RCC_CRRCR_HSI48RDY);
    }
    static void disable()
    {
        xmcu::bit::flag::clear(&(RCC->CRRCR), RCC_CRRCR_HSI48ON);
    }

    [[nodiscard]] static std::uint32_t get_calibration_value()
    {
        return xmcu::bit::flag::get(RCC->CRRCR, RCC_CRRCR_HSI48CAL);
    }

    [[nodiscard]] static std::uint32_t get_frequency_Hz()
    {
        return 48'000'000;
    }
};
} // namespace soc::st::arm::m0::u0::rm0503::oscillators