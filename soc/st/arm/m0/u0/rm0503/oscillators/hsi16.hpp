#pragma once

// CMSIS
#include <stm32u0xx.h>

// soc
#include <soc/assert.hpp>
#include <soc/bit_flag.hpp>
#include <soc/non_constructible.hpp>

namespace soc::st::arm::m0::u0::rm0503::oscillators {
namespace ll {
struct hsi16
{
    // ?
};
} // namespace ll

struct hsi16 : private non_constructible
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
        bit_flag::set(&(RCC->CR), RCC_CR_HSIASFS, static_cast<std::uint32_t>(descriptor_a.start_from_stop));
        bit_flag::set(&(RCC->CR), RCC_CR_HSIKERON, static_cast<std::uint32_t>(descriptor_a.power));
    }
    static Descriptor get_descriptor()
    {
        return {};
    }

    static void enable()
    {
        xmcu_assert(false == is_enabled());

        bit_flag::set(&(RCC->CR), RCC_CR_HSION);
    }
    static void disable()
    {
        xmcu_assert(true == is_enabled());

        bit_flag::clear(&(RCC->CR), RCC_CR_HSION);
    }

    static bool is_ready()
    {
        return bit_flag::is(RCC->CR, RCC_CR_HSIRDY);
    }

    static bool is_enabled()
    {
        return bit_flag::is(RCC->CR, RCC_CR_HSION);
    }

    static std::uint32_t get_frequency_Hz()
    {
        return 16'000'000u;
    }
};
} // namespace soc::st::arm::m0::u0::rm0503::oscillators