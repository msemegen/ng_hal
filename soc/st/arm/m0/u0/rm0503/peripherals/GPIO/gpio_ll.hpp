#pragma once

/*
 *	Name: gpio_ll.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// cmsis
#include <stm32u0xx.h>

// xmcu
#include <xmcu/Limited.hpp>
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>
#include <xmcu/non_copyable.hpp>

// soc
#include <soc/st/arm/m0/u0/rm0503/peripherals/GPIO/base.hpp>

namespace soc::st::arm::m0::u0::rm0503::peripherals::ll {
struct gpio_moder_descriptor : private xmcu::non_constructible
{
    static constexpr std::uint32_t mask = 0x3u;
    static constexpr std::uint32_t shift_multiplier = 2u;

    enum class Flag : std::uint32_t
    {
        input = 0x0u,
        output = 0x1u,
        af = 0x2u,
        analog = 0x3u
    };

    enum class Mask : std::uint32_t
    {
        mask = mask
    };
};
struct gpio_otyper_descriptor : private xmcu::non_constructible
{
    static constexpr std::uint32_t mask = 0x1u;
    static constexpr std::uint32_t shift_multiplier = 1u;

    enum class Flag : std::uint32_t
    {
        push_pull = 0x0u,
        open_drain = 0x1u,
    };

    enum class Mask : std::uint32_t
    {
        mask = mask
    };
};
struct gpio_ospeedr_descriptor : private xmcu::non_constructible
{
    static constexpr std::uint32_t mask = 0x3u;
    static constexpr std::uint32_t shift_multiplier = 2u;

    enum class Flag : std::uint32_t
    {
        low = 0x0u,
        medium = 0x1u,
        high = 0x2u,
        ultra = 0x3u
    };

    enum class Mask : std::uint32_t
    {
        mask = mask
    };
};
struct gpio_pupdr_descriptor : private xmcu::non_constructible
{
    static constexpr std::uint32_t mask = 0x3u;
    static constexpr std::uint32_t shift_multiplier = 2u;

    enum class Flag : std::uint32_t
    {
        none = 0x0u,
        pull_up = 0x1u,
        pull_down = 0x2u,
    };

    enum class Mask : std::uint32_t
    {
        mask = mask
    };
};
struct gpio_idr_descriptor : private xmcu::non_constructible
{
    static constexpr std::uint32_t mask = 0x1u;
    static constexpr std::uint32_t shift_multiplier = 1u;

    enum class Flag : std::uint32_t
    {
        low,
        high
    };

    enum class Mask : std::uint32_t
    {
        mask = mask
    };
};
struct gpio_odr_descriptor : private xmcu::non_constructible
{
    static constexpr std::uint32_t mask = 0x1u;
    static constexpr std::uint32_t shift_multiplier = 1u;

    enum class Flag : std::uint32_t
    {
        low,
        high
    };

    enum class Mask : std::uint32_t
    {
        mask = mask
    };
};
struct gpio_bsrr_descriptor : private xmcu::non_constructible
{
    static constexpr std::uint32_t mask = 0x10001u;
    static constexpr std::uint32_t shift_multiplier = 1u;

    enum class Flag : std::uint32_t
    {
        low = 0x1u,
        high = 0x1000u
    };

    enum class Mask : std::uint32_t
    {
        mask = mask
    };
};
struct gpio_lckr_descriptor : private xmcu::non_constructible
{
    static constexpr std::uint32_t mask = 0x1u;
    static constexpr std::uint32_t shift_multiplier = 1u;

    enum class Flag : std::uint32_t
    {
        unlocked = 0x0u,
        lock = 0x01u,
        key = 0x10u
    };

    enum class Mask : std::uint32_t
    {
        mask = mask
    };
};
struct gpio_afr_descriptor : private xmcu::non_constructible
{
    static constexpr std::uint32_t mask = 0xFu;
    static constexpr std::uint32_t shift_multiplier = 4u;

    enum class Flag : std::uint32_t
    {
        af0,
        af1,
        af2,
        af3,
        af4,
        af5,
        af6,
        af7,
        af8,
        af9,
        af10,
        af11,
        af12,
        af13,
        af14
    };

    enum class Mask : std::uint32_t
    {
        mask = mask
    };
};
struct gpio_brr_descriptor : private xmcu::non_constructible
{
    static constexpr std::uint32_t mask = 0x1u;
    static constexpr std::uint32_t shift_multiplier = 1u;

    enum class Flag : std::uint32_t
    {
        low = 0x0u,
        high = 0x0u
    };

    enum class Mask : std::uint32_t
    {
        mask = mask
    };
};

struct gpio_clock : private xmcu::non_constructible
{
    template<typename Type> static void enable() = delete;
    template<typename Type> static void disable() = delete;

    template<typename Type> static bool is_enabled() = delete;
};

struct gpio : public gpio_base
{
private:
    /*
     * W - write, R - read, C - clear
     */
    template<typename desc_t> struct Reg_wrc
    {
        using Flag = desc_t::Flag;
        using Mask = desc_t::Mask;
        enum class Data;

        Reg_wrc(const volatile Reg_wrc& other_a)
            : v(other_a.v)
        {
        }

        void zero()
        {
            this->v = static_cast<Data>(0x0u);
        }

        operator const Data() const
        {
            return this->v;
        }
        operator const Data*() const
        {
            return &(this->v);
        }

    protected:
        volatile Data v;
    };
    template<typename desc_t> struct Reg_r
    {
        using Flag = desc_t::Flag;
        using Mask = desc_t::Mask;
        enum class Data;

        Reg_r(const volatile Reg_r& other_a)
            : v(other_a.v)
        {
        }

        operator const Data() const
        {
            return this->v;
        }
        operator const Data*() const
        {
            return &(this->v);
        }

    protected:
        const volatile Data v;
    };
    template<typename desc_t> struct Reg_wc
    {
        using Flag = desc_t::Flag;
        using Mask = desc_t::Mask;
        enum class Data;

        Reg_wc(const volatile Reg_wc& other_a)
            : v(other_a.v)
        {
        }

        void zero()
        {
            this->v = 0x0u;
        }

        constexpr operator Data() const
        {
            return this->v;
        }
        operator const Data*() const
        {
            return &(this->v);
        }

    protected:
        volatile Data v;
    };
    template<typename desc_t> struct Reg_wr
    {
        using Flag = desc_t::Flag;
        enum class Data;

        operator const Data() const
        {
            return this->v;
        }
        operator const Data*() const
        {
            return &(this->v);
        }

    protected:
        volatile Data v;
    };

public:
    struct MODER : public Reg_wrc<gpio_moder_descriptor>
    {
        using enum gpio_moder_descriptor::Flag;
        using enum gpio_moder_descriptor::Mask;
        using Data = Reg_wrc<gpio_moder_descriptor>::Data;

        MODER& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
    };
    struct OTYPER : public Reg_wrc<gpio_otyper_descriptor>
    {
        using enum gpio_otyper_descriptor::Flag;
        using enum gpio_otyper_descriptor::Mask;
        using Data = Reg_wrc<gpio_otyper_descriptor>::Data;

        OTYPER& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
    };
    struct OSPEEDR : public Reg_wrc<gpio_ospeedr_descriptor>
    {
        using enum gpio_ospeedr_descriptor::Flag;
        using enum gpio_ospeedr_descriptor::Mask;
        using Data = Reg_wrc<gpio_ospeedr_descriptor>::Data;

        OSPEEDR& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
    };
    struct PUPDR : public Reg_wrc<gpio_pupdr_descriptor>
    {
        using enum gpio_pupdr_descriptor::Flag;
        using enum gpio_pupdr_descriptor::Mask;
        using Data = Reg_wrc<gpio_pupdr_descriptor>::Data;

        PUPDR& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
    };
    struct IDR : public Reg_r<gpio_idr_descriptor>
    {
        using enum gpio_idr_descriptor::Flag;
        using enum gpio_idr_descriptor::Mask;
        using Data = Reg_r<gpio_idr_descriptor>::Data;
    };
    struct ODR : public Reg_wc<gpio_odr_descriptor>
    {
        using enum gpio_odr_descriptor::Flag;
        using enum gpio_odr_descriptor::Mask;
        using Data = Reg_wc<gpio_odr_descriptor>::Data;

        ODR& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
    };
    struct BSRR : public Reg_wc<gpio_bsrr_descriptor>
    {
        using enum gpio_bsrr_descriptor::Flag;
        using enum gpio_bsrr_descriptor::Mask;
        using Data = Reg_wc<gpio_bsrr_descriptor>::Data;

        BSRR& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
    };
    struct LCKR : public Reg_wr<gpio_lckr_descriptor>
    {
        using enum gpio_lckr_descriptor::Flag;
        using Data = Reg_wr<gpio_lckr_descriptor>::Data;
    };
    struct AFR : public Reg_wrc<gpio_afr_descriptor>
    {
        using enum gpio_afr_descriptor::Flag;
        using enum gpio_afr_descriptor::Mask;
        using Data = Reg_wrc<gpio_afr_descriptor>::Data;

        AFR& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
    };
    struct BRR : public Reg_wrc<gpio_brr_descriptor>
    {
        using enum gpio_brr_descriptor::Flag;
        using enum gpio_brr_descriptor::Mask;
        using Data = Reg_wrc<gpio_brr_descriptor>::Data;

        BRR& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
    };

    struct Registers : xmcu::non_copyable
    {
        MODER moder;     // port mode register
        OTYPER otyper;   // port output type register
        OSPEEDR ospeedr; // port output speed register
        PUPDR pupdr;     // port pull-up/pull-down register
        IDR idr;         // port input data register
        ODR odr;         // port output data register
        BSRR bsrr;       // port bit set/reset  register
        LCKR lckr;       // port configuration lock register
        AFR afr[2];      // alternate function registers
        BRR brr;         // bit reset register
    };

    template<typename Port_t> [[nodiscard]] static constexpr Registers* registers() = delete;
};

// MODER
constexpr gpio::MODER::Data operator<<(gpio::MODER::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::MODER::Data>(static_cast<std::uint32_t>(flag_a) << (pin_a * gpio_moder_descriptor::shift_multiplier));
}
constexpr gpio::MODER::Data operator<<(gpio::MODER::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::MODER::Data>(static_cast<std::uint32_t>(mask_a) << (pin_a * gpio_moder_descriptor::shift_multiplier));
}
constexpr gpio::MODER::Data operator>>(gpio::MODER::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::MODER::Data>(static_cast<std::uint32_t>(flag_a) >> (pin_a * gpio_moder_descriptor::shift_multiplier));
}
constexpr gpio::MODER::Data operator>>(gpio::MODER::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::MODER::Data>(static_cast<std::uint32_t>(mask_a) >> (pin_a * gpio_moder_descriptor::shift_multiplier));
}
constexpr gpio::MODER::Data operator|(gpio::MODER::Data left_a, gpio::MODER::Data right_a)
{
    return static_cast<gpio::MODER::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::MODER::Data operator&(gpio::MODER::Data value_a, gpio::MODER::Data mask_a)
{
    return static_cast<gpio::MODER::Data>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio::MODER::Flag operator~(gpio::MODER::Flag flag_a)
{
    return static_cast<gpio::MODER::Flag>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::MODER::Mask operator~(gpio::MODER::Mask flag_a)
{
    return static_cast<gpio::MODER::Mask>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::MODER::Data operator~(gpio::MODER::Data flag_a)
{
    return static_cast<gpio::MODER::Data>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::MODER::Data operator^(gpio::MODER::Data left_a, std::uint32_t right_a)
{
    return static_cast<gpio::MODER::Data>(static_cast<std::uint32_t>(left_a) ^ right_a);
}

// OTYPER
constexpr gpio::OTYPER::Data operator<<(gpio::OTYPER::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::OTYPER::Data>(static_cast<std::uint32_t>(flag_a) << (pin_a * gpio_otyper_descriptor::shift_multiplier));
}
constexpr gpio::OTYPER::Data operator<<(gpio::OTYPER::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::OTYPER::Data>(static_cast<std::uint32_t>(mask_a) << (pin_a * gpio_otyper_descriptor::shift_multiplier));
}
constexpr gpio::OTYPER::Data operator>>(gpio::OTYPER::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::OTYPER::Data>(static_cast<std::uint32_t>(flag_a) >> (pin_a * gpio_otyper_descriptor::shift_multiplier));
}
constexpr gpio::OTYPER::Data operator>>(gpio::OTYPER::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::OTYPER::Data>(static_cast<std::uint32_t>(mask_a) >> (pin_a * gpio_otyper_descriptor::shift_multiplier));
}
constexpr gpio::OTYPER::Data operator|(gpio::OTYPER::Data left_a, gpio::OTYPER::Data right_a)
{
    return static_cast<gpio::OTYPER::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::OTYPER::Data operator&(gpio::OTYPER::Data value_a, gpio::OTYPER::Data mask_a)
{
    return static_cast<gpio::OTYPER::Data>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio::OTYPER::Flag operator~(gpio::OTYPER::Flag flag_a)
{
    return static_cast<gpio::OTYPER::Flag>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::OTYPER::Mask operator~(gpio::OTYPER::Mask flag_a)
{
    return static_cast<gpio::OTYPER::Mask>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::OTYPER::Data operator~(gpio::OTYPER::Data flag_a)
{
    return static_cast<gpio::OTYPER::Data>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::OTYPER::Data operator^(gpio::OTYPER::Data left_a, std::uint32_t right_a)
{
    return static_cast<gpio::OTYPER::Data>(static_cast<std::uint32_t>(left_a) ^ right_a);
}

// OSPEEDR
constexpr gpio::OSPEEDR::Data operator<<(gpio::OSPEEDR::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::OSPEEDR::Data>(static_cast<std::uint32_t>(flag_a) << (pin_a * gpio_ospeedr_descriptor::shift_multiplier));
}
constexpr gpio::OSPEEDR::Data operator<<(gpio::OSPEEDR::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::OSPEEDR::Data>(static_cast<std::uint32_t>(mask_a) << (pin_a * gpio_ospeedr_descriptor::shift_multiplier));
}
constexpr gpio::OSPEEDR::Data operator>>(gpio::OSPEEDR::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::OSPEEDR::Data>(static_cast<std::uint32_t>(flag_a) >> (pin_a * gpio_ospeedr_descriptor::shift_multiplier));
}
constexpr gpio::OSPEEDR::Data operator>>(gpio::OSPEEDR::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::OSPEEDR::Data>(static_cast<std::uint32_t>(mask_a) >> (pin_a * gpio_ospeedr_descriptor::shift_multiplier));
}
constexpr gpio::OSPEEDR::Data operator|(gpio::OSPEEDR::Data left_a, gpio::OSPEEDR::Data right_a)
{
    return static_cast<gpio::OSPEEDR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::OSPEEDR::Data operator&(gpio::OSPEEDR::Data value_a, gpio::OSPEEDR::Data mask_a)
{
    return static_cast<gpio::OSPEEDR::Data>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio::OSPEEDR::Flag operator~(gpio::OSPEEDR::Flag flag_a)
{
    return static_cast<gpio::OSPEEDR::Flag>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::OSPEEDR::Mask operator~(gpio::OSPEEDR::Mask flag_a)
{
    return static_cast<gpio::OSPEEDR::Mask>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::OSPEEDR::Data operator~(gpio::OSPEEDR::Data flag_a)
{
    return static_cast<gpio::OSPEEDR::Data>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::OSPEEDR::Data operator^(gpio::OSPEEDR::Data left_a, std::uint32_t right_a)
{
    return static_cast<gpio::OSPEEDR::Data>(static_cast<std::uint32_t>(left_a) ^ right_a);
}

// PUPDR
constexpr gpio::PUPDR::Data operator<<(gpio::PUPDR::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::PUPDR::Data>(static_cast<std::uint32_t>(flag_a) << (pin_a * gpio_pupdr_descriptor::shift_multiplier));
}
constexpr gpio::PUPDR::Data operator<<(gpio::PUPDR::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::PUPDR::Data>(static_cast<std::uint32_t>(mask_a) << (pin_a * gpio_pupdr_descriptor::shift_multiplier));
}
constexpr gpio::PUPDR::Flag operator>>(gpio::PUPDR::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::PUPDR::Flag>(static_cast<std::uint32_t>(flag_a) >> (pin_a * gpio_pupdr_descriptor::shift_multiplier));
}
constexpr gpio::PUPDR::Data operator|(gpio::PUPDR::Data left_a, gpio::PUPDR::Data right_a)
{
    return static_cast<gpio::PUPDR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::PUPDR::Data operator&(gpio::PUPDR::Data value_a, gpio::PUPDR::Data mask_a)
{
    return static_cast<gpio::PUPDR::Data>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio::PUPDR::Flag operator~(gpio::PUPDR::Flag flag_a)
{
    return static_cast<gpio::PUPDR::Flag>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::PUPDR::Mask operator~(gpio::PUPDR::Mask flag_a)
{
    return static_cast<gpio::PUPDR::Mask>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::PUPDR::Data operator~(gpio::PUPDR::Data flag_a)
{
    return static_cast<gpio::PUPDR::Data>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::PUPDR::Data operator^(gpio::PUPDR::Data left_a, std::uint32_t right_a)
{
    return static_cast<gpio::PUPDR::Data>(static_cast<std::uint32_t>(left_a) ^ right_a);
}

// IDR
constexpr gpio::IDR::Data operator<<(gpio::IDR::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::IDR::Data>(static_cast<std::uint32_t>(flag_a) << (pin_a * gpio_idr_descriptor::shift_multiplier));
}
constexpr gpio::IDR::Data operator<<(gpio::IDR::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::IDR::Data>(static_cast<std::uint32_t>(mask_a) << (pin_a * gpio_idr_descriptor::shift_multiplier));
}
constexpr gpio::IDR::Flag operator>>(gpio::IDR::Data mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::IDR::Flag>(static_cast<std::uint32_t>(mask_a) >> (pin_a * gpio_idr_descriptor::shift_multiplier));
}
constexpr gpio::IDR::Data operator|(gpio::IDR::Data left_a, gpio::IDR::Data right_a)
{
    return static_cast<gpio::IDR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::IDR::Data operator&(gpio::IDR::Data value_a, gpio::IDR::Data mask_a)
{
    return static_cast<gpio::IDR::Data>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio::IDR::Flag operator~(gpio::IDR::Flag flag_a)
{
    return static_cast<gpio::IDR::Flag>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::IDR::Mask operator~(gpio::IDR::Mask flag_a)
{
    return static_cast<gpio::IDR::Mask>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::IDR::Data operator~(gpio::IDR::Data flag_a)
{
    return static_cast<gpio::IDR::Data>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::IDR::Data operator^(gpio::IDR::Data left_a, std::uint32_t right_a)
{
    return static_cast<gpio::IDR::Data>(static_cast<std::uint32_t>(left_a) ^ right_a);
}

// ODR
constexpr gpio::ODR::Data operator<<(gpio::ODR::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::ODR::Data>(static_cast<std::uint32_t>(flag_a) << (pin_a * gpio_odr_descriptor::shift_multiplier));
}
constexpr gpio::ODR::Data operator<<(gpio::ODR::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::ODR::Data>(static_cast<std::uint32_t>(mask_a) << (pin_a * gpio_odr_descriptor::shift_multiplier));
}
constexpr gpio::ODR::Data operator>>(gpio::ODR::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::ODR::Data>(static_cast<std::uint32_t>(flag_a) >> (pin_a * gpio_pupdr_descriptor::shift_multiplier));
}
constexpr gpio::ODR::Data operator>>(gpio::ODR::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::ODR::Data>(static_cast<std::uint32_t>(mask_a) >> (pin_a * gpio_pupdr_descriptor::shift_multiplier));
}
constexpr gpio::ODR::Data operator>>(gpio::ODR::Data mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::ODR::Data>(static_cast<std::uint32_t>(mask_a) >> (pin_a * gpio_odr_descriptor::shift_multiplier));
}
constexpr gpio::ODR::Data operator|(gpio::ODR::Data left_a, gpio::ODR::Data right_a)
{
    return static_cast<gpio::ODR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::ODR::Data operator&(gpio::ODR::Data value_a, gpio::ODR::Data mask_a)
{
    return static_cast<gpio::ODR::Data>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio::ODR::Flag operator~(gpio::ODR::Flag flag_a)
{
    return static_cast<gpio::ODR::Flag>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::ODR::Mask operator~(gpio::ODR::Mask flag_a)
{
    return static_cast<gpio::ODR::Mask>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::ODR::Data operator~(gpio::ODR::Data flag_a)
{
    return static_cast<gpio::ODR::Data>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::ODR::Data operator^(gpio::ODR::Data left_a, std::uint32_t right_a)
{
    return static_cast<gpio::ODR::Data>(static_cast<std::uint32_t>(left_a) ^ right_a);
}

// BSRR
constexpr gpio::BSRR::Data operator<<(gpio::BSRR::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::BSRR::Data>(static_cast<std::uint32_t>(flag_a) << (pin_a * gpio_bsrr_descriptor::shift_multiplier));
}
constexpr gpio::BSRR::Data operator<<(gpio::BSRR::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::BSRR::Data>(static_cast<std::uint32_t>(mask_a) << (pin_a * gpio_bsrr_descriptor::shift_multiplier));
}
constexpr gpio::BSRR::Data operator>>(gpio::BSRR::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::BSRR::Data>(static_cast<std::uint32_t>(flag_a) >> (pin_a * gpio_pupdr_descriptor::shift_multiplier));
}
constexpr gpio::BSRR::Data operator>>(gpio::BSRR::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::BSRR::Data>(static_cast<std::uint32_t>(mask_a) >> (pin_a * gpio_pupdr_descriptor::shift_multiplier));
}
constexpr gpio::BSRR::Data operator|(gpio::BSRR::Data left_a, gpio::BSRR::Data right_a)
{
    return static_cast<gpio::BSRR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::BSRR::Data operator&(gpio::BSRR::Data value_a, gpio::BSRR::Data mask_a)
{
    return static_cast<gpio::BSRR::Data>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio::BSRR::Flag operator~(gpio::BSRR::Flag flag_a)
{
    return static_cast<gpio::BSRR::Flag>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::BSRR::Mask operator~(gpio::BSRR::Mask flag_a)
{
    return static_cast<gpio::BSRR::Mask>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::BSRR::Data operator~(gpio::BSRR::Data flag_a)
{
    return static_cast<gpio::BSRR::Data>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::BSRR::Data operator^(gpio::BSRR::Data left_a, std::uint32_t right_a)
{
    return static_cast<gpio::BSRR::Data>(static_cast<std::uint32_t>(left_a) ^ right_a);
}

// LCKR
constexpr gpio::LCKR::Data operator<<(gpio::LCKR::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::LCKR::Data>(static_cast<std::uint32_t>(flag_a) << (pin_a * gpio_lckr_descriptor::shift_multiplier));
}
constexpr gpio::LCKR::Data operator|(gpio::LCKR::Data left_a, gpio::LCKR::Data right_a)
{
    return static_cast<gpio::LCKR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::LCKR::Data operator|(gpio::LCKR::Flag flag_a, gpio::LCKR::Data mask_a)
{
    assert(flag_a == gpio::LCKR::key);
    return static_cast<gpio::LCKR::Data>((static_cast<std::uint32_t>(flag_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio::LCKR::Data operator|(gpio::LCKR::Data mask_a, gpio::LCKR::Flag flag_a)
{
    assert(flag_a == gpio::LCKR::key);
    return static_cast<gpio::LCKR::Data>((static_cast<std::uint32_t>(flag_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio::LCKR::Data operator&(gpio::LCKR::Data value_a, gpio::LCKR::Data mask_a)
{
    return static_cast<gpio::LCKR::Data>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio::LCKR::Flag operator~(gpio::LCKR::Flag flag_a)
{
    return static_cast<gpio::LCKR::Flag>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::LCKR::Data operator~(gpio::LCKR::Data flag_a)
{
    return static_cast<gpio::LCKR::Data>(~static_cast<std::uint32_t>(flag_a));
}

// AFR
constexpr gpio::AFR::Data operator<<(gpio::AFR::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::AFR::Data>(static_cast<std::uint32_t>(flag_a) << (pin_a * gpio_afr_descriptor::shift_multiplier));
}
constexpr gpio::AFR::Data operator<<(gpio::AFR::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::AFR::Data>(static_cast<std::uint32_t>(mask_a) << (pin_a * gpio_afr_descriptor::shift_multiplier));
}
constexpr gpio::AFR::Data operator>>(gpio::AFR::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::AFR::Data>(static_cast<std::uint32_t>(flag_a) >> (pin_a * gpio_pupdr_descriptor::shift_multiplier));
}
constexpr gpio::AFR::Data operator>>(gpio::AFR::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::AFR::Data>(static_cast<std::uint32_t>(mask_a) >> (pin_a * gpio_pupdr_descriptor::shift_multiplier));
}
constexpr gpio::AFR::Data operator|(gpio::AFR::Data left_a, gpio::AFR::Data right_a)
{
    return static_cast<gpio::AFR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::AFR::Data operator&(gpio::AFR::Data value_a, gpio::AFR::Data mask_a)
{
    return static_cast<gpio::AFR::Data>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio::AFR::Flag operator~(gpio::AFR::Flag flag_a)
{
    return static_cast<gpio::AFR::Flag>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::AFR::Mask operator~(gpio::AFR::Mask flag_a)
{
    return static_cast<gpio::AFR::Mask>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::AFR::Data operator~(gpio::AFR::Data flag_a)
{
    return static_cast<gpio::AFR::Data>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::AFR::Data operator^(gpio::AFR::Data left_a, std::uint32_t right_a)
{
    return static_cast<gpio::AFR::Data>(static_cast<std::uint32_t>(left_a) ^ right_a);
}

// BRR
constexpr gpio::BRR::Data operator<<(gpio::BRR::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::BRR::Data>(static_cast<std::uint32_t>(flag_a) << (pin_a * gpio_brr_descriptor::shift_multiplier));
}
constexpr gpio::BRR::Data operator<<(gpio::BRR::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::BRR::Data>(static_cast<std::uint32_t>(mask_a) << (pin_a * gpio_brr_descriptor::shift_multiplier));
}
constexpr gpio::BRR::Data operator>>(gpio::BRR::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::BRR::Data>(static_cast<std::uint32_t>(flag_a) >> (pin_a * gpio_pupdr_descriptor::shift_multiplier));
}
constexpr gpio::BRR::Data operator>>(gpio::BRR::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::BRR::Data>(static_cast<std::uint32_t>(mask_a) >> (pin_a * gpio_pupdr_descriptor::shift_multiplier));
}
constexpr gpio::BRR::Data operator|(gpio::BRR::Data left_a, gpio::BRR::Data right_a)
{
    return static_cast<gpio::BRR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::BRR::Data operator&(gpio::BRR::Data value_a, gpio::BRR::Data mask_a)
{
    return static_cast<gpio::BRR::Data>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio::BRR::Flag operator~(gpio::BRR::Flag flag_a)
{
    return static_cast<gpio::BRR::Flag>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::BRR::Mask operator~(gpio::BRR::Mask flag_a)
{
    return static_cast<gpio::BRR::Mask>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::BRR::Data operator~(gpio::BRR::Data flag_a)
{
    return static_cast<gpio::BRR::Data>(~static_cast<std::uint32_t>(flag_a));
}
constexpr gpio::BRR::Data operator^(gpio::BRR::Data left_a, std::uint32_t right_a)
{
    return static_cast<gpio::BRR::Data>(static_cast<std::uint32_t>(left_a) ^ right_a);
}

#if defined XMCU_GPIOA_PRESENT
template<> [[nodiscard]] constexpr gpio::Registers* gpio::registers<gpio::A>()
{
    return reinterpret_cast<gpio::Registers*>(GPIOA_BASE);
}

template<> inline void gpio_clock::enable<gpio::A>()
{
    xmcu::bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIOAEN);
}
template<> inline void gpio_clock::disable<gpio::A>()
{
    xmcu::bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIOAEN);
}
template<> inline bool gpio_clock::is_enabled<gpio::A>()
{
    return xmcu::bit::flag::is(RCC->IOPENR, RCC_IOPENR_GPIOAEN);
}

constexpr gpio::MODER::Data operator<<(gpio::MODER::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::MODER::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_moder_descriptor::shift_multiplier)));
}
constexpr gpio::MODER::Data operator<<(gpio::MODER::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::MODER::Data>(mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_moder_descriptor::shift_multiplier));
}

constexpr gpio::OTYPER::Data operator<<(gpio::OTYPER::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::OTYPER::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_otyper_descriptor::shift_multiplier)));
}
constexpr gpio::OTYPER::Data operator<<(gpio::OTYPER::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::OTYPER::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_otyper_descriptor::shift_multiplier)));
}

constexpr gpio::OSPEEDR::Data operator<<(gpio::OSPEEDR::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::OSPEEDR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio::OSPEEDR::Data operator<<(gpio::OSPEEDR::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::OSPEEDR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_ospeedr_descriptor::shift_multiplier)));
}

constexpr gpio::PUPDR::Data operator<<(gpio::PUPDR::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::PUPDR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_pupdr_descriptor::shift_multiplier)));
}
constexpr gpio::PUPDR::Data operator<<(gpio::PUPDR::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::PUPDR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_pupdr_descriptor::shift_multiplier)));
}

constexpr gpio::IDR::Data operator<<(gpio::IDR::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::IDR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_idr_descriptor::shift_multiplier)));
}
constexpr gpio::IDR::Data operator<<(gpio::IDR::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::IDR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_idr_descriptor::shift_multiplier)));
}

constexpr gpio::ODR::Data operator<<(gpio::ODR::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::ODR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}
constexpr gpio::ODR::Data operator<<(gpio::ODR::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::ODR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}

constexpr gpio::BSRR::Data operator<<(gpio::BSRR::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::BSRR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}
constexpr gpio::BSRR::Data operator<<(gpio::BSRR::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::BSRR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}

constexpr gpio::LCKR::Data operator<<(gpio::LCKR::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::LCKR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_lckr_descriptor::shift_multiplier)));
}

constexpr gpio::AFR::Data operator<<(gpio::AFR::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::AFR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
constexpr gpio::AFR::Data operator<<(gpio::AFR::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::AFR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}

constexpr gpio::BRR::Data operator<<(gpio::BRR::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::BRR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
constexpr gpio::BRR::Data operator<<(gpio::BRR::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::BRR::Data>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
#endif
#if defined XMCU_GPIOB_PRESENT
template<> [[nodiscard]] constexpr gpio::Registers* gpio::registers<gpio::B>()
{
    return reinterpret_cast<gpio::Registers*>(GPIOB_BASE);
}

template<> inline void gpio_clock::enable<gpio::B>()
{
    xmcu::bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIOBEN);
}
template<> inline void gpio_clock::disable<gpio::B>()
{
    xmcu::bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIOBEN);
}
template<> inline bool gpio_clock::is_enabled<gpio::B>()
{
    return xmcu::bit::flag::is(RCC->IOPENR, RCC_IOPENR_GPIOBEN);
}

constexpr gpio::MODER::Data operator<<(gpio::MODER::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::MODER::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_moder_descriptor::shift_multiplier)));
}
constexpr gpio::MODER::Data operator<<(gpio::MODER::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::MODER::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_moder_descriptor::shift_multiplier)));
}

constexpr gpio::OTYPER::Data operator<<(gpio::OTYPER::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::OTYPER::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_otyper_descriptor::shift_multiplier)));
}
constexpr gpio::OTYPER::Data operator<<(gpio::OTYPER::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::OTYPER::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_otyper_descriptor::shift_multiplier)));
}

constexpr gpio::OSPEEDR::Data operator<<(gpio::OSPEEDR::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::OSPEEDR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio::OSPEEDR::Data operator<<(gpio::OSPEEDR::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::OSPEEDR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_ospeedr_descriptor::shift_multiplier)));
}

constexpr gpio::PUPDR::Data operator<<(gpio::PUPDR::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::PUPDR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_pupdr_descriptor::shift_multiplier)));
}
constexpr gpio::PUPDR::Data operator<<(gpio::PUPDR::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::PUPDR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_pupdr_descriptor::shift_multiplier)));
}

constexpr gpio::IDR::Data operator<<(gpio::IDR::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::IDR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_idr_descriptor::shift_multiplier)));
}
constexpr gpio::IDR::Data operator<<(gpio::IDR::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::IDR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_idr_descriptor::shift_multiplier)));
}

constexpr gpio::ODR::Data operator<<(gpio::ODR::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::ODR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}
constexpr gpio::ODR::Data operator<<(gpio::ODR::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::ODR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}

constexpr gpio::BSRR::Data operator<<(gpio::BSRR::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::BSRR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}
constexpr gpio::BSRR::Data operator<<(gpio::BSRR::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::BSRR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}

constexpr gpio::LCKR::Data operator<<(gpio::LCKR::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::LCKR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_lckr_descriptor::shift_multiplier)));
}

constexpr gpio::AFR::Data operator<<(gpio::AFR::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::AFR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
constexpr gpio::AFR::Data operator<<(gpio::AFR::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::AFR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}

constexpr gpio::BRR::Data operator<<(gpio::BRR::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::BRR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
constexpr gpio::BRR::Data operator<<(gpio::BRR::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::BRR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
#endif
#if defined XMCU_GPIOC_PRESENT
template<> [[nodiscard]] constexpr gpio::Registers* gpio::registers<gpio::C>()
{
    return reinterpret_cast<gpio::Registers*>(GPIOC_BASE);
}

template<> inline void gpio_clock::enable<gpio::C>()
{
    xmcu::bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIOCEN);
}
template<> inline void gpio_clock::disable<gpio::C>()
{
    xmcu::bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIOCEN);
}
template<> inline bool gpio_clock::is_enabled<gpio::C>()
{
    return xmcu::bit::flag::is(RCC->IOPENR, RCC_IOPENR_GPIOCEN);
}

constexpr gpio::MODER::Data operator<<(gpio::MODER::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::MODER::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_moder_descriptor::shift_multiplier)));
}
constexpr gpio::MODER::Data operator<<(gpio::MODER::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::MODER::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_moder_descriptor::shift_multiplier)));
}

constexpr gpio::OTYPER::Data operator<<(gpio::OTYPER::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::OTYPER::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_otyper_descriptor::shift_multiplier)));
}
constexpr gpio::OTYPER::Data operator<<(gpio::OTYPER::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::OTYPER::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_otyper_descriptor::shift_multiplier)));
}

constexpr gpio::OSPEEDR::Data operator<<(gpio::OSPEEDR::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::OSPEEDR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio::OSPEEDR::Data operator<<(gpio::OSPEEDR::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::OSPEEDR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_ospeedr_descriptor::shift_multiplier)));
}

constexpr gpio::PUPDR::Data operator<<(gpio::PUPDR::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::PUPDR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_pupdr_descriptor::shift_multiplier)));
}
constexpr gpio::PUPDR::Data operator<<(gpio::PUPDR::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::PUPDR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_pupdr_descriptor::shift_multiplier)));
}

constexpr gpio::IDR::Data operator<<(gpio::IDR::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::IDR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_idr_descriptor::shift_multiplier)));
}
constexpr gpio::IDR::Data operator<<(gpio::IDR::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::IDR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_idr_descriptor::shift_multiplier)));
}

constexpr gpio::ODR::Data operator<<(gpio::ODR::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::ODR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}
constexpr gpio::ODR::Data operator<<(gpio::ODR::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::ODR::Data>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}

constexpr gpio::BSRR::Data operator<<(gpio::BSRR::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::BSRR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}
constexpr gpio::BSRR::Data operator<<(gpio::BSRR::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::BSRR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}

constexpr gpio::LCKR::Data operator<<(gpio::LCKR::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::LCKR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}

constexpr gpio::AFR::Data operator<<(gpio::AFR::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::AFR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
constexpr gpio::AFR::Data operator<<(gpio::AFR::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::AFR::Data>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}

constexpr gpio::BRR::Data operator<<(gpio::BRR::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::BRR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
constexpr gpio::BRR::Data operator<<(gpio::BRR::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::BRR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
#endif
#if defined XMCU_GPIOD_PRESENT
template<> [[nodiscard]] constexpr gpio::Registers* gpio::registers<gpio::D>()
{
    return reinterpret_cast<gpio::Registers*>(GPIOD_BASE);
}

template<> inline void gpio_clock::enable<gpio::D>()
{
    xmcu::bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIODEN);
}
template<> inline void gpio_clock::disable<gpio::D>()
{
    xmcu::bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIODEN);
}
template<> inline bool gpio_clock::is_enabled<gpio::D>()
{
    return xmcu::bit::flag::is(RCC->IOPENR, RCC_IOPENR_GPIODEN);
}

constexpr gpio::MODER::Data operator<<(gpio::MODER::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::MODER::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_moder_descriptor::shift_multiplier)));
}
constexpr gpio::MODER::Data operator<<(gpio::MODER::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::MODER::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_moder_descriptor::shift_multiplier)));
}

constexpr gpio::OTYPER::Data operator<<(gpio::OTYPER::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::OTYPER::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_otyper_descriptor::shift_multiplier)));
}
constexpr gpio::OTYPER::Data operator<<(gpio::OTYPER::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::OTYPER::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_otyper_descriptor::shift_multiplier)));
}

constexpr gpio::OSPEEDR::Data operator<<(gpio::OSPEEDR::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::OSPEEDR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio::OSPEEDR::Data operator<<(gpio::OSPEEDR::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::OSPEEDR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_ospeedr_descriptor::shift_multiplier)));
}

constexpr gpio::PUPDR::Data operator<<(gpio::PUPDR::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::PUPDR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_pupdr_descriptor::shift_multiplier)));
}
constexpr gpio::PUPDR::Data operator<<(gpio::PUPDR::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::PUPDR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_pupdr_descriptor::shift_multiplier)));
}

constexpr gpio::IDR::Data operator<<(gpio::IDR::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::IDR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_idr_descriptor::shift_multiplier)));
}
constexpr gpio::IDR::Data operator<<(gpio::IDR::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::IDR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_idr_descriptor::shift_multiplier)));
}

constexpr gpio::ODR::Data operator<<(gpio::ODR::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::ODR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}
constexpr gpio::ODR::Data operator<<(gpio::ODR::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::ODR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}

constexpr gpio::BSRR::Data operator<<(gpio::BSRR::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::BSRR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_bsrr_descriptor::shift_multiplier)));
}
constexpr gpio::BSRR::Data operator<<(gpio::BSRR::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::BSRR::Data>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * gpio_bsrr_descriptor::shift_multiplier)));
}

constexpr gpio::LCKR::Data operator<<(gpio::LCKR::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::LCKR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_lckr_descriptor::shift_multiplier)));
}

constexpr gpio::AFR::Data operator<<(gpio::AFR::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::AFR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
constexpr gpio::AFR::Data operator<<(gpio::AFR::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::AFR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}

constexpr gpio::BRR::Data operator<<(gpio::BRR::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::BRR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
constexpr gpio::BRR::Data operator<<(gpio::BRR::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::BRR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
#endif
#if defined XMCU_GPIOF_PRESENT
template<> [[nodiscard]] constexpr gpio::Registers* gpio::registers<gpio::F>()
{
    return reinterpret_cast<gpio::Registers*>(GPIOF_BASE);
}

template<> inline void gpio_clock::enable<gpio::F>()
{
    xmcu::bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIOFEN);
}
template<> inline void gpio_clock::disable<gpio::F>()
{
    xmcu::bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIOFEN);
}
template<> inline bool gpio_clock::is_enabled<gpio::F>()
{
    return xmcu::bit::flag::is(RCC->IOPENR, RCC_IOPENR_GPIOFEN);
}

constexpr gpio::MODER::Data operator<<(gpio::MODER::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::MODER::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_moder_descriptor::shift_multiplier)));
}
constexpr gpio::MODER::Data operator<<(gpio::MODER::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::MODER::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_moder_descriptor::shift_multiplier)));
}

constexpr gpio::OTYPER::Data operator<<(gpio::OTYPER::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::OTYPER::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_otyper_descriptor::shift_multiplier)));
}
constexpr gpio::OTYPER::Data operator<<(gpio::OTYPER::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::OTYPER::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_otyper_descriptor::shift_multiplier)));
}

constexpr gpio::OSPEEDR::Data operator<<(gpio::OSPEEDR::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::OSPEEDR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio::OSPEEDR::Data operator<<(gpio::OSPEEDR::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::OSPEEDR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_ospeedr_descriptor::shift_multiplier)));
}

constexpr gpio::PUPDR::Data operator<<(gpio::PUPDR::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::PUPDR::Data>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * gpio_pupdr_descriptor::shift_multiplier)));
}
constexpr gpio::PUPDR::Data operator<<(gpio::PUPDR::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::PUPDR::Data>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * gpio_pupdr_descriptor::shift_multiplier)));
}

constexpr gpio::IDR::Data operator<<(gpio::IDR::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::IDR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_idr_descriptor::shift_multiplier)));
}
constexpr gpio::IDR::Data operator<<(gpio::IDR::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::IDR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_idr_descriptor::shift_multiplier)));
}

constexpr gpio::ODR::Data operator<<(gpio::ODR::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::ODR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}
constexpr gpio::ODR::Data operator<<(gpio::ODR::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::ODR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}

constexpr gpio::BSRR::Data operator<<(gpio::BSRR::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::BSRR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}
constexpr gpio::BSRR::Data operator<<(gpio::BSRR::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::BSRR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_odr_descriptor::shift_multiplier)));
}

constexpr gpio::LCKR::Data operator<<(gpio::LCKR::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::LCKR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_lckr_descriptor::shift_multiplier)));
}

constexpr gpio::AFR::Data operator<<(gpio::AFR::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::AFR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
constexpr gpio::AFR::Data operator<<(gpio::AFR::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::AFR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}

constexpr gpio::BRR::Data operator<<(gpio::BRR::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::BRR::Data>((flag_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
constexpr gpio::BRR::Data operator<<(gpio::BRR::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::BRR::Data>((mask_a << (static_cast<std::uint32_t>(pin_a) * gpio_afr_descriptor::shift_multiplier)));
}
#endif
} // namespace soc::st::arm::m0::u0::rm0503::peripherals::ll