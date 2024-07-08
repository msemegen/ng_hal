#pragma once

/*
 */

// CMSIS
#include <stm32u0xx.h>

// std
#include <cassert>
#include <chrono>
#include <cstdint>

// soc
#include <soc/bit_flag.hpp>
#include <soc/non_constructible.hpp>
#include <soc/various.hpp>

namespace {
constexpr std::uint32_t freq_Hz_lut[] = { 100u,       200u,       400u,        800u,        1'000'000u,  2'000'000u,
                                          4'000'000u, 8'000'000u, 16'000'000u, 24'000'000u, 32'000'000u, 48'000'000u };
}

namespace soc::st::arm::m0::u0::rm0503::oscillators {
namespace ll {
struct msi
{
    // ?
};
} // namespace ll

struct msi : private non_constructible
{
    struct Descriptor
    {
        std::uint8_t trimm = 0x0u;
        std::uint8_t calibration = 0x0u;
    };

    struct Run
    {
        enum class Frequency : std::uint32_t
        {
            _100_kHz = RCC_CR_MSIRANGE_0,
            _200_kHz = RCC_CR_MSIRANGE_1,
            _400_kHz = RCC_CR_MSIRANGE_2,
            _800_kHz = RCC_CR_MSIRANGE_3,
            _1_MHz = RCC_CR_MSIRANGE_4,
            _2_MHz = RCC_CR_MSIRANGE_5,
            _4_MHz = RCC_CR_MSIRANGE_6,
            _8_MHz = RCC_CR_MSIRANGE_7,
            _16_MHz = RCC_CR_MSIRANGE_8,
            _24_MHz = RCC_CR_MSIRANGE_9,
            _32_MHz = RCC_CR_MSIRANGE_10,
            _48_MHz = RCC_CR_MSIRANGE_11,
        };

        static void set_frequency(Frequency frequency_a)
        {
            assert(false == bit_flag::is(RCC->CR, RCC_CR_MSION) || true == bit_flag::is(RCC->CR, RCC_CR_MSIRDY));

            bit_flag::set(&(RCC->CR), RCC_CR_MSIRANGE, static_cast<std::uint32_t>(frequency_a));
        }

        static void set_active()
        {
            bit_flag::set(&(RCC->CR), RCC_CR_MSIRGSEL);
        }

        static bool is_active()
        {
            return bit_flag::is(RCC->CR, RCC_CR_MSIRGSEL);
        }

        static Frequency get_frequency()
        {
            return static_cast<Frequency>(bit_flag::get(RCC->CR, RCC_CR_MSIRANGE));
        }
    };

    struct Standby
    {
        enum class Frequency : std::uint32_t
        {
            _1_MHz = RCC_CSR_MSISTBYRG_1,
            _2_MHz = RCC_CSR_MSISTBYRG_2,
            _4_MHz = RCC_CSR_MSISTBYRG_4,
            _8_MHz = RCC_CSR_MSISTBYRG_8,
        };

        static void set_frequency(Frequency frequency_a)
        {
            assert(true == bit_flag::is(RCC->CR, RCC_CR_MSIRGSEL));

            bit_flag::set(&(RCC->CSR), RCC_CSR_MSISTBYRG, static_cast<std::uint32_t>(frequency_a));
        }

        static bool is_active()
        {
            return false == bit_flag::is(RCC->CR, RCC_CR_MSIRGSEL);
        }

        static Frequency get_frequency()
        {
            return static_cast<Frequency>(bit_flag::get(RCC->CSR, RCC_CSR_MSISTBYRG));
        }
    };

    static void set_descriptor(const Descriptor& descriptor_a)
    {
        bit_flag::set(&(RCC->ICSCR), 0xFFu, static_cast<std::uint32_t>(descriptor_a.calibration) & 0xFFu);
        bit_flag::set(&(RCC->ICSCR), 0xFF00u, (static_cast<std::uint32_t>(descriptor_a.trimm) << 8) & 0xFF00u);
    }
    static Descriptor get_descriptor()
    {
        return {};
    }

    static void enable()
    {
        assert(false == is_enabled());

        bit_flag::set(&(RCC->CR), RCC_CR_MSION);
    }
    static void disable()
    {
        assert(true == is_enabled());

        bit_flag::clear(&(RCC->CR), RCC_CR_MSION);
    }

    static bool is_enabled()
    {
        return bit_flag::is(RCC->CR, RCC_CR_MSION);
    }

    static bool is_ready()
    {
        return bit_flag::is(RCC->CR, RCC_CR_MSIRDY);
    }

    static std::uint32_t get_frequency_Hz()
    {
        if (true == standby.is_active())
        {
            return freq_Hz_lut[bit_flag::get(RCC->CR, RCC_CR_MSIRANGE) >> RCC_CR_MSIRANGE_Pos];
        }
        else
        {
            return freq_Hz_lut[bit_flag::get(RCC->CSR, RCC_CSR_MSISTBYRG) >> RCC_CSR_MSISTBYRG_Pos];
        }
    }

    static Run run;
    static Standby standby;
};
} // namespace soc::st::arm::m0::u0::rm0503::oscillators