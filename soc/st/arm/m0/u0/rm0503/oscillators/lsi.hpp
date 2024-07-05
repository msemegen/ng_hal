#pragma once

// CMSIS
#include <stm32u0xx.h>

// std
#include <cstdint>

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
    };

    static void set_descriptor(const Descriptor& descriptor_a) {}

    static bool is_enabled()
    {
        return bit_flag::is(RCC->CSR, RCC_CSR_LSION);
    }

    static bool is_ready()
    {
        return bit_flag::is(RCC->CSR, RCC_CSR_LSIRDY);
    }
};
} // namespace soc::st::arm::m0::u0::rm0503::oscillators