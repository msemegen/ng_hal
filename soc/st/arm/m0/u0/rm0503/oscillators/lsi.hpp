#pragma once

/*
 *	Name: lsi.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cassert>
#include <cstdint>

// CMSIS
#include <stm32u0xx.h>

// xmcu
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>

namespace soc::st::arm::m0::u0::rm0503::oscillators {
namespace ll {
struct lsi
{
};
} // namespace ll

struct lsi : private xmcu::non_constructible
{
    struct Descriptor
    {
        enum class Prescaler : std::uint32_t
        {
            _1,
            _128
        };

        Prescaler prescaler;
    };

    static void set_descriptor(const Descriptor& descriptor_a)
    {
        assert(false == is_enabled());

        xmcu::bit::flag::set(&(RCC->CSR), RCC_CSR_LSIPREDIV, static_cast<std::uint32_t>(descriptor_a.prescaler));
    }

    static void enable()
    {
        assert(false == is_enabled());

        xmcu::bit::flag::set(&(RCC->CSR), RCC_CSR_LSION);
    }

    static bool is_enabled()
    {
        return xmcu::bit::flag::is(RCC->CSR, RCC_CSR_LSION);
    }

    static bool is_ready()
    {
        return xmcu::bit::flag::is(RCC->CSR, RCC_CSR_LSIRDY);
    }

    static std::uint32_t get_frequency_Hz()
    {
        return 32'000u;
    }
};
} // namespace soc::st::arm::m0::u0::rm0503::oscillators