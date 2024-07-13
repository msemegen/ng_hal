#pragma once

/*
 *	Name: bit_flag.hpp
 *
 *   Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *   Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>

// xmcu
#include <xmcu/non_constructible.hpp>

namespace xmcu {
class bit_flag : private non_constructible
{
public:
    template<typename Register_t, typename Flag_t> constexpr static inline bool is(Register_t a_register, Flag_t a_flag)
    {
        return a_flag == (a_register & a_flag);
    }

    template<typename Register_t, typename Mask_t> constexpr static inline Mask_t get(Register_t a_register, Mask_t a_mask)
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
} // namespace xmcu
