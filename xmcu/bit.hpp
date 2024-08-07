#pragma once

/*
 *	Name: bit.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <chrono>
#include <cstdint>

// xmcu
#include <xmcu/non_constructible.hpp>

namespace xmcu {
struct bit : private non_constructible
{
    template<typename Register_t> [[nodiscard]] constexpr static bool is(Register_t a_register, uint8_t a_index)
    {
        const Register_t flag = static_cast<Register_t>(0x1u) << a_index;
        return flag == (a_register & flag);
    }

    template<typename Register_t, typename Mask_t> [[nodiscard]] constexpr static bool is_any(Register_t a_register, Mask_t a_mask)
    {
        return static_cast<Register_t>(0u) != (a_register & a_mask);
    }

    template<typename Register_t> constexpr static void set(Register_t* a_p_register, uint8_t a_index)
    {
        (*a_p_register) = (*a_p_register) | (static_cast<Register_t>(0x1u) << a_index);
    }

    template<typename Register_t> constexpr static void clear(Register_t* a_p_register, uint8_t a_index)
    {
        (*a_p_register) = (*a_p_register) & ~(static_cast<Register_t>(0x1u) << a_index);
    }

    template<typename Register_t> constexpr static void toggle(Register_t* a_p_register, uint8_t a_index)
    {
        (*a_p_register) = (*a_p_register) ^ (static_cast<Register_t>(0x1u) << a_index);
    }

    struct flag : private non_constructible
    {
        template<typename Register_t, typename Flag_t> [[nodiscard]] constexpr static inline bool is(Register_t a_register, Flag_t a_flag)
        {
            return a_flag == (a_register & a_flag);
        }

        template<typename Register_t, typename Mask_t>
        [[nodiscard]] constexpr static inline Mask_t get(Register_t a_register, Mask_t a_mask)
        {
            return (a_register & a_mask);
        }

        template<typename Register_t, typename Flag_t> constexpr static inline void set(Register_t* a_p_register, Flag_t a_flag)
        {
            (*a_p_register) = (*a_p_register) | a_flag;
        }

        template<typename Register_t, typename Clear_mask_t, typename Flag_t>
        constexpr static inline void set(Register_t* a_p_register, Clear_mask_t a_clear_mask, Flag_t a_set_flag)
        {
            (*a_p_register) = ((*a_p_register & (~a_clear_mask)) | a_set_flag);
        }

        template<typename Register_t, typename Flag_t> constexpr static inline void clear(Register_t* a_p_register, Flag_t a_flag)
        {
            (*a_p_register) = (*a_p_register) & ~a_flag;
        }
    };

    struct wait_for : private non_constructible
    {
        static void all_set(volatile const std::uint32_t& register_a, std::uint32_t mask_a)
        {
            while (false == bit::flag::is(register_a, mask_a))
                ;
        }

        static void any_set(volatile const std::uint32_t& register_a, std::uint32_t mask_a)
        {
            while (false == bit::is_any(register_a, mask_a))
                ;
        }

        static void all_cleared(volatile const std::uint32_t& register_a, std::uint32_t mask_a)
        {
            while (false == bit::flag::is(~register_a, mask_a))
                ;
        }

        static void any_cleared(volatile const std::uint32_t& register_a, std::uint32_t mask_a)
        {
            while (false == bit::is_any(~register_a, mask_a))
                ;
        }

        static bool all_set(volatile const std::uint32_t& register_a, std::uint32_t mask_a, std::chrono::milliseconds timeout_a)
        {
            const std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + timeout_a;
            bool status = false;

            while (std::chrono::steady_clock::now() < timeout && false == status)
            {
                status = bit::flag::is(register_a, mask_a);
            }

            return status;
        }

        static bool any_set(volatile const std::uint32_t& register_a, std::uint32_t mask_a, std::chrono::milliseconds timeout_a)
        {
            const std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + timeout_a;
            bool status = false;

            while (std::chrono::steady_clock::now() < timeout && false == status)
            {
                status = bit::is_any(register_a, mask_a);
            }

            return status;
        }

        static bool
        all_cleared(volatile const std::uint32_t& register_a, std::uint32_t mask_a, std::chrono::milliseconds timeout_a)
        {
            const std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + timeout_a;
            bool status = false;

            while (std::chrono::steady_clock::now() < timeout && false == status)
            {
                status = bit::flag::is(~register_a, mask_a);
            }

            return status;
        }

        static bool any_cleared(volatile const std::uint32_t& register_a, std::uint32_t mask_a, std::chrono::milliseconds timeout_a)
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
};
} // namespace xmcu
