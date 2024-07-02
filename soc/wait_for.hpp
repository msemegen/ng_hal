#pragma once

// std
#include <chrono>

// soc
#include <soc/bit.hpp>
#include <soc/bit_flag.hpp>
#include <soc/non_constructible.hpp>

namespace soc {
struct wait_for : private non_constructible
{
    static void all_bits_are_set(volatile const std::uint32_t& register_a, std::uint32_t mask_a)
    {
        while (false == bit_flag::is(register_a, mask_a))
            ;
    }

    static void any_bit_is_set(volatile const std::uint32_t& register_a, std::uint32_t mask_a)
    {
        while (false == bit::is_any(register_a, mask_a))
            ;
    }

    static void all_bits_are_cleared(volatile const std::uint32_t& register_a, std::uint32_t mask_a)
    {
        while (false == bit_flag::is(~register_a, mask_a))
            ;
    }

    static void any_bit_is_cleared(volatile const std::uint32_t& register_a, std::uint32_t mask_a)
    {
        while (false == bit::is_any(~register_a, mask_a))
            ;
    }

    static bool all_bits_are_set(volatile const std::uint32_t& register_a, std::uint32_t mask_a, std::chrono::milliseconds timeout_a)
    {
        const std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + timeout_a;
        bool status = false;

        while (std::chrono::steady_clock::now() < timeout && false == status)
        {
            status = bit_flag::is(register_a, mask_a);
        }

        return status;
    }

    static bool any_bit_is_set(volatile const std::uint32_t& register_a, std::uint32_t mask_a, std::chrono::milliseconds timeout_a)
    {
        const std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + timeout_a;
        bool status = false;

        while (std::chrono::steady_clock::now() < timeout && false == status)
        {
            status = bit::is_any(register_a, mask_a);
        }

        return status;
    }

    static bool all_bits_are_cleared(volatile const std::uint32_t& register_a, std::uint32_t mask_a, std::chrono::milliseconds timeout_a)
    {
        const std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + timeout_a;
        bool status = false;

        while (std::chrono::steady_clock::now() < timeout && false == status)
        {
            status = bit_flag::is(~register_a, mask_a);
        }

        return status;
    }

    static bool any_bit_is_cleared(volatile const std::uint32_t& register_a, std::uint32_t mask_a, std::chrono::milliseconds timeout_a)
    {
        const std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + timeout_a;
        bool status = false;

        while (std::chrono::steady_clock::now() < timeout && false == status)
        {
            status = bit::is_any(~register_a, mask_a);
        }

        return status;
    }
};
} // namespace soc