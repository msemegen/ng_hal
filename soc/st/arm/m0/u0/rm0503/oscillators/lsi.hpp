#pragma once

// CMSIS
#include <stm32u0xx.h>

// std
#include <cstdint>
#include <cassert>

// soc
#include <soc/bit_flag.hpp>
#include <soc/non_constructible.hpp>

namespace soc::st::arm::m0::u0::rm0503::oscillators {
namespace ll {
struct lsi
{
};
} // namespace ll

struct lsi : private non_constructible
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

        bit_flag::set(&(RCC->CSR), RCC_CSR_LSIPREDIV, static_cast<std::uint32_t>(descriptor_a.prescaler));
    }

    static void enable()
    {
        assert(false == is_enabled());

        bit_flag::set(&(RCC->CSR), RCC_CSR_LSION);
    }

    static bool is_enabled()
    {
        return bit_flag::is(RCC->CSR, RCC_CSR_LSION);
    }

    static bool is_ready()
    {
        return bit_flag::is(RCC->CSR, RCC_CSR_LSIRDY);
    }

    static std::uint32_t get_frequency_Hz()
    {
        return 32'000u;
    }
};
} // namespace soc::st::arm::m0::u0::rm0503::oscillators