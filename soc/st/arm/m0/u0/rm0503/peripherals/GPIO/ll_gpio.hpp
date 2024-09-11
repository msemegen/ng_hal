#pragma once

/*
 *	Name: gpio.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// xmcu
#include <xmcu/Limited.hpp>
#include <xmcu/non_constructible.hpp>

// soc
#include <soc/st/arm/m0/u0/rm0503/peripherals/GPIO/base.hpp>

namespace soc::st::arm::m0::u0::rm0503::peripherals::ll {
struct moder_descriptor : private xmcu::non_constructible
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
struct otyper_descriptor : private xmcu::non_constructible
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
struct ospeedr_descriptor : private xmcu::non_constructible
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
struct pupdr_descriptor : private xmcu::non_constructible
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
struct idr_descriptor : private xmcu::non_constructible
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
struct odr_descriptor : private xmcu::non_constructible
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
struct bsrr_descriptor : private xmcu::non_constructible
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
struct lckr_descriptor : private xmcu::non_constructible
{
    static constexpr std::uint32_t mask = 0x1u;
    static constexpr std::uint32_t shift_multiplier = 1u;

    enum class Flag : std::uint32_t
    {
        unlocked = 0x0u,
        lock = 0x01u,
        key = 0x10u
    };
};
struct afr_descriptor : private xmcu::non_constructible
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
struct brr_descriptor : private xmcu::non_constructible
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

struct gpio_clock2 : private xmcu::non_constructible
{
    template<typename Type> static void enable() = delete;
    template<typename Type> static void disable() = delete;

    template<typename Type> static bool is_enabled() = delete;
};

struct gpio2 : public gpio_base
{
private:
    /*
     * W - write, R - read, C - clear
     */
    template<typename desc_t> struct WRC_reg
    {
        using Flag = desc_t::Flag;
        using Mask = desc_t::Mask;
        enum class Value : std::uint32_t;

        constexpr void set(Value value_a)
        {
            xmcu::bit::flag::set(&(this->v), static_cast<std::uint32_t>(value_a));
        }
        constexpr void set(Value clear_a, Value value_a)
        {
            xmcu::bit::flag::set(&(this->v), static_cast<std::uint32_t>(clear_a), static_cast<std::uint32_t>(value_a));
        }

        constexpr void clear(Value value_a)
        {
            xmcu::bit::flag::clear(&(this->v), static_cast<std::uint32_t>(value_a));
        }

        void zero()
        {
            this->v = 0x0u;
        }
        template<typename Pin_t> void toggle(Pin_t pin_a) = delete;

        template<typename Pin_t> Value get(Pin_t pin_a) const = delete;
        constexpr operator std::uint32_t() const
        {
            return this->v;
        }
        constexpr operator Value() const
        {
            return static_cast<Value>(this->v);
        }

    protected:
        volatile std::uint32_t v;
    };
    template<typename desc_t> struct R_reg
    {
        using Flag = desc_t::Flag;
        using Mask = desc_t::Mask;
        enum class Value : std::uint32_t;

        template<typename Pin_t> Value get(Pin_t pin_a) const = delete;
        constexpr operator std::uint32_t() const
        {
            return this->v;
        }
        constexpr operator Value() const
        {
            return static_cast<Value>(this->v);
        }

    protected:
        volatile std::uint32_t v;
    };
    template<typename desc_t> struct WC_reg
    {
        using Flag = desc_t::Flag;
        using Mask = desc_t::Mask;
        enum class Value : std::uint32_t;

        constexpr void set(Value value_a)
        {
            xmcu::bit::flag::set(&(this->v), static_cast<std::uint32_t>(value_a));
        }
        constexpr void set(Value clear_a, Value value_a)
        {
            xmcu::bit::flag::set(&(this->v), static_cast<std::uint32_t>(clear_a), static_cast<std::uint32_t>(value_a));
        }

        constexpr void clear(Value value_a)
        {
            xmcu::bit::flag::clear(&(this->v), static_cast<std::uint32_t>(value_a));
        }

        void zero()
        {
            this->v = 0x0u;
        }
        template<typename Pin_t> void toggle(Pin_t pin_a) = delete;

    protected:
        volatile std::uint32_t v;
    };
    template<typename desc_t> struct WR_reg
    {
        using Flag = desc_t::Flag;
        enum class Value : std::uint32_t;

        constexpr void set(Value value_a)
        {
            xmcu::bit::flag::set(&(this->v), static_cast<std::uint32_t>(value_a));
        }
        constexpr void set(Value clear_a, Value value_a)
        {
            xmcu::bit::flag::set(&(this->v), static_cast<std::uint32_t>(clear_a), static_cast<std::uint32_t>(value_a));
        }

        void zero()
        {
            this->v = 0x0u;
        }
        template<typename Pin_t> void toggle(Pin_t pin_a) = delete;

    protected:
        volatile std::uint32_t v;
    };

public:
    struct Moder : public WRC_reg<moder_descriptor>
    {
        using enum moder_descriptor::Flag;
        using enum moder_descriptor::Mask;
        using Value = WRC_reg<moder_descriptor>::Value;
    };
    struct Otyper : public WRC_reg<otyper_descriptor>
    {
        using enum moder_descriptor::Flag;
        using enum moder_descriptor::Mask;
        using Value = WRC_reg<otyper_descriptor>::Value;
    };
    struct Ospeedr : public WRC_reg<ospeedr_descriptor>
    {
        using enum ospeedr_descriptor::Flag;
        using enum ospeedr_descriptor::Mask;
        using Value = WRC_reg<ospeedr_descriptor>::Value;
    };
    struct Pupdr : public WRC_reg<pupdr_descriptor>
    {
        using enum pupdr_descriptor::Flag;
        using enum pupdr_descriptor::Mask;
        using Value = WRC_reg<pupdr_descriptor>::Value;
    };
    struct Idr : public R_reg<idr_descriptor>
    {
        using enum idr_descriptor::Flag;
        using enum idr_descriptor::Mask;
        using Value = WRC_reg<idr_descriptor>::Value;
    };
    struct Odr : public WC_reg<odr_descriptor>
    {
        using enum odr_descriptor::Flag;
        using enum odr_descriptor::Mask;
        using Value = WC_reg<odr_descriptor>::Value;
    };
    struct Bsrr : public WC_reg<bsrr_descriptor>
    {
        using enum bsrr_descriptor::Flag;
        using enum bsrr_descriptor::Mask;
        using Value = WC_reg<bsrr_descriptor>::Value;
    };
    struct Lckr : public WR_reg<lckr_descriptor>
    {
        using enum lckr_descriptor::Flag;
        using Value = WR_reg<lckr_descriptor>::Value;
    };
    struct Afr : public WRC_reg<afr_descriptor>
    {
        using enum afr_descriptor::Flag;
        using enum afr_descriptor::Mask;
        using Value = WRC_reg<afr_descriptor>::Value;
    };
    struct Brr : public WRC_reg<brr_descriptor>
    {
        using enum brr_descriptor::Flag;
        using enum brr_descriptor::Mask;
        using Value = WRC_reg<brr_descriptor>::Value;
    };

    struct Port
    {
        Moder moder;     // port mode register
        Otyper otyper;   // port output type register
        Ospeedr ospeedr; // port output speed register
        Pupdr pupdr;     // port pull-up/pull-down register
        Idr idr;         // port input data register
        Odr odr;         // port output data register
        Bsrr bsrr;       // port bit set/reset  register
        Lckr lckr;       // port configuration lock register
        Afr afr[3];      // alternate function registers
        Brr brr;         // bit reset register
    };

    template<typename Port_t> [[nodiscard]] static constexpr Port* port() = delete;
};

constexpr gpio2::Moder::Value operator<<(gpio2::Moder::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Moder::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * moder_descriptor::shift_multiplier));
}
constexpr gpio2::Moder::Value operator<<(gpio2::Moder::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Moder::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * moder_descriptor::shift_multiplier));
}

constexpr gpio2::Otyper::Value operator<<(gpio2::Otyper::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Otyper::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * otyper_descriptor::shift_multiplier));
}
constexpr gpio2::Otyper::Value operator<<(gpio2::Otyper::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Otyper::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * otyper_descriptor::shift_multiplier));
}

constexpr gpio2::Ospeedr::Value operator<<(gpio2::Ospeedr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Ospeedr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * ospeedr_descriptor::shift_multiplier));
}
constexpr gpio2::Ospeedr::Value operator<<(gpio2::Ospeedr::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Ospeedr::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * ospeedr_descriptor::shift_multiplier));
}

constexpr gpio2::Pupdr::Value operator<<(gpio2::Pupdr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Pupdr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * pupdr_descriptor::shift_multiplier));
}
constexpr gpio2::Pupdr::Value operator<<(gpio2::Pupdr::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Pupdr::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * pupdr_descriptor::shift_multiplier));
}

constexpr gpio2::Idr::Value operator<<(gpio2::Idr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Idr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * idr_descriptor::shift_multiplier));
}
constexpr gpio2::Idr::Value operator<<(gpio2::Idr::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Idr::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * idr_descriptor::shift_multiplier));
}

constexpr gpio2::Odr::Value operator<<(gpio2::Odr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Odr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * odr_descriptor::shift_multiplier));
}
constexpr gpio2::Odr::Value operator<<(gpio2::Odr::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Odr::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * odr_descriptor::shift_multiplier));
}

constexpr gpio2::Bsrr::Value operator<<(gpio2::Bsrr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Bsrr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * odr_descriptor::shift_multiplier));
}
constexpr gpio2::Bsrr::Value operator<<(gpio2::Bsrr::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Bsrr::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * odr_descriptor::shift_multiplier));
}

constexpr gpio2::Lckr::Value operator<<(gpio2::Lckr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Lckr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * lckr_descriptor::shift_multiplier));
}

constexpr gpio2::Afr::Value operator<<(gpio2::Afr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Afr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * afr_descriptor::shift_multiplier));
}
constexpr gpio2::Afr::Value operator<<(gpio2::Afr::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Afr::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * odr_descriptor::shift_multiplier));
}

constexpr gpio2::Brr::Value operator<<(gpio2::Brr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Brr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * afr_descriptor::shift_multiplier));
}
constexpr gpio2::Brr::Value operator<<(gpio2::Brr::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio2::Brr::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * odr_descriptor::shift_multiplier));
}

#if defined XMCU_GPIOA_PRESENT
template<> [[nodiscard]] constexpr gpio2::Port* gpio2::port<gpio2::A>()
{
    return reinterpret_cast<gpio2::Port*>(GPIOA_BASE);
}

template<> inline void gpio_clock2::enable<gpio2::A>()
{
    xmcu::bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIOAEN);
}
template<> inline void gpio_clock2::disable<gpio2::A>()
{
    xmcu::bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIOAEN);
}
template<> inline bool gpio_clock2::is_enabled<gpio2::A>()
{
    return xmcu::bit::flag::is(RCC->IOPENR, RCC_IOPENR_GPIOAEN);
}

template<> template<> void gpio2::WRC_reg<moder_descriptor>::toggle<gpio2::A>(gpio2::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), moder_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<moder_descriptor>::Value gpio2::WRC_reg<moder_descriptor>::get<gpio2::A>(gpio2::A pin_a) const
{
    return static_cast<gpio2::WRC_reg<moder_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier) & moder_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<otyper_descriptor>::toggle<gpio2::A>(gpio2::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            otyper_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<otyper_descriptor>::Value gpio2::WRC_reg<otyper_descriptor>::get<gpio2::A>(gpio2::A pin_a) const
{
    return static_cast<gpio2::WRC_reg<otyper_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier) & otyper_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<ospeedr_descriptor>::toggle<gpio2::A>(gpio2::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            ospeedr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<ospeedr_descriptor>::Value gpio2::WRC_reg<ospeedr_descriptor>::get<gpio2::A>(gpio2::A pin_a) const
{
    return static_cast<gpio2::WRC_reg<ospeedr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier) & ospeedr_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<pupdr_descriptor>::toggle<gpio2::A>(gpio2::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), pupdr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<pupdr_descriptor>::Value gpio2::WRC_reg<pupdr_descriptor>::get<gpio2::A>(gpio2::A pin_a) const
{
    return static_cast<gpio2::WRC_reg<pupdr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & pupdr_descriptor::mask);
}

template<> template<> gpio2::R_reg<idr_descriptor>::Value gpio2::R_reg<idr_descriptor>::get<gpio2::A>(gpio2::A pin_a) const
{
    return static_cast<gpio2::R_reg<idr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & idr_descriptor::mask);
}

template<> template<> void gpio2::WC_reg<odr_descriptor>::toggle<gpio2::A>(gpio2::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), odr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier));
}

template<> template<> void gpio2::WC_reg<bsrr_descriptor>::toggle<gpio2::A>(gpio2::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), bsrr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * bsrr_descriptor::shift_multiplier));
}

template<> template<> void gpio2::WRC_reg<afr_descriptor>::toggle<gpio2::A>(gpio2::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<afr_descriptor>::Value gpio2::WRC_reg<afr_descriptor>::get<gpio2::A>(gpio2::A pin_a) const
{
    return static_cast<gpio2::WRC_reg<afr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier) & afr_descriptor::mask);
}

template<> template<> void gpio2::WC_reg<brr_descriptor>::toggle<gpio2::A>(gpio2::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}

constexpr gpio2::Moder::Value operator<<(gpio2::Moder::Flag flag_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Moder::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio2::Moder::Value operator<<(gpio2::Moder::Mask mask_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Moder::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio2::Moder::Value operator|(gpio2::Moder::Value left_a, gpio2::Moder::Value right_a)
{
    return static_cast<gpio2::Moder::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Moder::Value operator&(gpio2::Moder::Value value_a, gpio2::Moder::Value mask_a)
{
    return static_cast<gpio2::Moder::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Otyper::Value operator<<(gpio2::Otyper::Flag flag_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Otyper::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio2::Otyper::Value operator<<(gpio2::Otyper::Mask mask_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Otyper::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio2::Otyper::Value operator|(gpio2::Otyper::Value left_a, gpio2::Otyper::Value right_a)
{
    return static_cast<gpio2::Otyper::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Otyper::Value operator&(gpio2::Otyper::Value value_a, gpio2::Otyper::Value mask_a)
{
    return static_cast<gpio2::Otyper::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Ospeedr::Value operator<<(gpio2::Ospeedr::Flag flag_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Ospeedr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio2::Ospeedr::Value operator<<(gpio2::Ospeedr::Mask mask_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Ospeedr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio2::Ospeedr::Value operator|(gpio2::Ospeedr::Value left_a, gpio2::Otyper::Value right_a)
{
    return static_cast<gpio2::Ospeedr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Ospeedr::Value operator&(gpio2::Ospeedr::Value value_a, gpio2::Ospeedr::Value mask_a)
{
    return static_cast<gpio2::Ospeedr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Pupdr::Value operator<<(gpio2::Pupdr::Flag flag_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Pupdr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio2::Pupdr::Value operator<<(gpio2::Pupdr::Mask mask_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Pupdr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio2::Pupdr::Value operator|(gpio2::Pupdr::Value left_a, gpio2::Pupdr::Value right_a)
{
    return static_cast<gpio2::Pupdr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Pupdr::Value operator&(gpio2::Pupdr::Value value_a, gpio2::Pupdr::Value mask_a)
{
    return static_cast<gpio2::Pupdr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Idr::Value operator<<(gpio2::Idr::Flag flag_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Idr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio2::Idr::Value operator<<(gpio2::Idr::Mask mask_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Idr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio2::Idr::Value operator|(gpio2::Idr::Value left_a, gpio2::Idr::Value right_a)
{
    return static_cast<gpio2::Idr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Idr::Value operator&(gpio2::Idr::Value value_a, gpio2::Idr::Value mask_a)
{
    return static_cast<gpio2::Idr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Odr::Value operator<<(gpio2::Odr::Flag flag_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Odr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Odr::Value operator<<(gpio2::Odr::Mask mask_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Odr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Odr::Value operator|(gpio2::Odr::Value left_a, gpio2::Odr::Value right_a)
{
    return static_cast<gpio2::Odr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Odr::Value operator&(gpio2::Odr::Value value_a, gpio2::Odr::Value mask_a)
{
    return static_cast<gpio2::Odr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Bsrr::Value operator<<(gpio2::Bsrr::Flag flag_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Bsrr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Bsrr::Value operator<<(gpio2::Bsrr::Mask mask_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Bsrr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Bsrr::Value operator|(gpio2::Bsrr::Value left_a, gpio2::Bsrr::Value right_a)
{
    return static_cast<gpio2::Bsrr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Bsrr::Value operator&(gpio2::Bsrr::Value value_a, gpio2::Bsrr::Value mask_a)
{
    return static_cast<gpio2::Bsrr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Lckr::Value operator<<(gpio2::Lckr::Flag flag_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Lckr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Value left_a, gpio2::Lckr::Value right_a)
{
    return static_cast<gpio2::Lckr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Flag flag_a, gpio2::Lckr::Value mask_a)
{
    assert(flag_a == gpio2::Lckr::key);
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(flag_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Value mask_a, gpio2::Lckr::Flag flag_a)
{
    assert(flag_a == gpio2::Lckr::key);
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(flag_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio2::Lckr::Value operator&(gpio2::Lckr::Value value_a, gpio2::Lckr::Value mask_a)
{
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Afr::Value operator<<(gpio2::Afr::Flag flag_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Afr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Afr::Value operator<<(gpio2::Afr::Mask mask_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Afr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Afr::Value operator|(gpio2::Afr::Value left_a, gpio2::Afr::Value right_a)
{
    return static_cast<gpio2::Afr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Afr::Value operator&(gpio2::Afr::Value value_a, gpio2::Afr::Value mask_a)
{
    return static_cast<gpio2::Afr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Brr::Value operator<<(gpio2::Brr::Flag flag_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Brr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Brr::Value operator<<(gpio2::Brr::Mask mask_a, gpio2::A pin_a)
{
    return static_cast<gpio2::Brr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Brr::Value operator|(gpio2::Brr::Value left_a, gpio2::Brr::Value right_a)
{
    return static_cast<gpio2::Brr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Brr::Value operator&(gpio2::Brr::Value value_a, gpio2::Brr::Value mask_a)
{
    return static_cast<gpio2::Brr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
#endif
#if defined XMCU_GPIOB_PRESENT
template<> [[nodiscard]] constexpr gpio2::Port* gpio2::port<gpio2::B>()
{
    return reinterpret_cast<gpio2::Port*>(GPIOB_BASE);
}

template<> inline void gpio_clock2::enable<gpio2::B>()
{
    xmcu::bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIOBEN);
}
template<> inline void gpio_clock2::disable<gpio2::B>()
{
    xmcu::bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIOBEN);
}
template<> inline bool gpio_clock2::is_enabled<gpio2::B>()
{
    return xmcu::bit::flag::is(RCC->IOPENR, RCC_IOPENR_GPIOBEN);
}

template<> template<> void gpio2::WRC_reg<moder_descriptor>::toggle<gpio2::B>(gpio2::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), moder_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<moder_descriptor>::Value gpio2::WRC_reg<moder_descriptor>::get<gpio2::B>(gpio2::B pin_a) const
{
    return static_cast<gpio2::WRC_reg<moder_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier) & moder_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<otyper_descriptor>::toggle<gpio2::B>(gpio2::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            otyper_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<otyper_descriptor>::Value gpio2::WRC_reg<otyper_descriptor>::get<gpio2::B>(gpio2::B pin_a) const
{
    return static_cast<gpio2::WRC_reg<otyper_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier) & otyper_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<ospeedr_descriptor>::toggle<gpio2::B>(gpio2::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            ospeedr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<ospeedr_descriptor>::Value gpio2::WRC_reg<ospeedr_descriptor>::get<gpio2::B>(gpio2::B pin_a) const
{
    return static_cast<gpio2::WRC_reg<ospeedr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier) & ospeedr_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<pupdr_descriptor>::toggle<gpio2::B>(gpio2::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), pupdr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<pupdr_descriptor>::Value gpio2::WRC_reg<pupdr_descriptor>::get<gpio2::B>(gpio2::B pin_a) const
{
    return static_cast<gpio2::WRC_reg<pupdr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & pupdr_descriptor::mask);
}

template<> template<> gpio2::R_reg<idr_descriptor>::Value gpio2::R_reg<idr_descriptor>::get<gpio2::B>(gpio2::B pin_a) const
{
    return static_cast<gpio2::R_reg<idr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & idr_descriptor::mask);
}

template<> template<> void gpio2::WC_reg<odr_descriptor>::toggle<gpio2::B>(gpio2::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), odr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier));
}

template<> template<> void gpio2::WC_reg<bsrr_descriptor>::toggle<gpio2::B>(gpio2::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), bsrr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * bsrr_descriptor::shift_multiplier));
}

template<> template<> void gpio2::WRC_reg<afr_descriptor>::toggle<gpio2::B>(gpio2::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<afr_descriptor>::Value gpio2::WRC_reg<afr_descriptor>::get<gpio2::B>(gpio2::B pin_a) const
{
    return static_cast<gpio2::WRC_reg<afr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier) & afr_descriptor::mask);
}

template<> template<> void gpio2::WC_reg<brr_descriptor>::toggle<gpio2::B>(gpio2::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}

constexpr gpio2::Moder::Value operator<<(gpio2::Moder::Flag flag_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Moder::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio2::Moder::Value operator<<(gpio2::Moder::Mask mask_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Moder::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio2::Moder::Value operator|(gpio2::Moder::Value left_a, gpio2::Moder::Value right_a)
{
    return static_cast<gpio2::Moder::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Moder::Value operator&(gpio2::Moder::Value value_a, gpio2::Moder::Value mask_a)
{
    return static_cast<gpio2::Moder::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Otyper::Value operator<<(gpio2::Otyper::Flag flag_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Otyper::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio2::Otyper::Value operator<<(gpio2::Otyper::Mask mask_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Otyper::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio2::Otyper::Value operator|(gpio2::Otyper::Value left_a, gpio2::Otyper::Value right_a)
{
    return static_cast<gpio2::Otyper::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Otyper::Value operator&(gpio2::Otyper::Value value_a, gpio2::Otyper::Value mask_a)
{
    return static_cast<gpio2::Otyper::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Ospeedr::Value operator<<(gpio2::Ospeedr::Flag flag_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Ospeedr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio2::Ospeedr::Value operator<<(gpio2::Ospeedr::Mask mask_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Ospeedr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio2::Ospeedr::Value operator|(gpio2::Ospeedr::Value left_a, gpio2::Otyper::Value right_a)
{
    return static_cast<gpio2::Ospeedr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Ospeedr::Value operator&(gpio2::Ospeedr::Value value_a, gpio2::Ospeedr::Value mask_a)
{
    return static_cast<gpio2::Ospeedr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Pupdr::Value operator<<(gpio2::Pupdr::Flag flag_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Pupdr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio2::Pupdr::Value operator<<(gpio2::Pupdr::Mask mask_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Pupdr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio2::Pupdr::Value operator|(gpio2::Pupdr::Value left_a, gpio2::Pupdr::Value right_a)
{
    return static_cast<gpio2::Pupdr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Pupdr::Value operator&(gpio2::Pupdr::Value value_a, gpio2::Pupdr::Value mask_a)
{
    return static_cast<gpio2::Pupdr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Idr::Value operator<<(gpio2::Idr::Flag flag_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Idr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio2::Idr::Value operator<<(gpio2::Idr::Mask mask_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Idr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio2::Idr::Value operator|(gpio2::Idr::Value left_a, gpio2::Idr::Value right_a)
{
    return static_cast<gpio2::Idr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Idr::Value operator&(gpio2::Idr::Value value_a, gpio2::Idr::Value mask_a)
{
    return static_cast<gpio2::Idr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Odr::Value operator<<(gpio2::Odr::Flag flag_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Odr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Odr::Value operator<<(gpio2::Odr::Mask mask_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Odr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Odr::Value operator|(gpio2::Odr::Value left_a, gpio2::Odr::Value right_a)
{
    return static_cast<gpio2::Odr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Odr::Value operator&(gpio2::Odr::Value value_a, gpio2::Odr::Value mask_a)
{
    return static_cast<gpio2::Odr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Bsrr::Value operator<<(gpio2::Bsrr::Flag flag_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Bsrr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Bsrr::Value operator<<(gpio2::Bsrr::Mask mask_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Bsrr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Bsrr::Value operator|(gpio2::Bsrr::Value left_a, gpio2::Bsrr::Value right_a)
{
    return static_cast<gpio2::Bsrr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Bsrr::Value operator&(gpio2::Bsrr::Value value_a, gpio2::Bsrr::Value mask_a)
{
    return static_cast<gpio2::Bsrr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Lckr::Value operator<<(gpio2::Lckr::Flag flag_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Lckr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Value left_a, gpio2::Lckr::Value right_a)
{
    return static_cast<gpio2::Lckr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Flag flag_a, gpio2::Lckr::Value mask_a)
{
    assert(flag_a == gpio2::Lckr::key);
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(flag_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Value mask_a, gpio2::Lckr::Flag flag_a)
{
    assert(flag_a == gpio2::Lckr::key);
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(flag_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio2::Lckr::Value operator&(gpio2::Lckr::Value value_a, gpio2::Lckr::Value mask_a)
{
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Afr::Value operator<<(gpio2::Afr::Flag flag_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Afr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Afr::Value operator<<(gpio2::Afr::Mask mask_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Afr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Afr::Value operator|(gpio2::Afr::Value left_a, gpio2::Afr::Value right_a)
{
    return static_cast<gpio2::Afr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Afr::Value operator&(gpio2::Afr::Value value_a, gpio2::Afr::Value mask_a)
{
    return static_cast<gpio2::Afr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Brr::Value operator<<(gpio2::Brr::Flag flag_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Brr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Brr::Value operator<<(gpio2::Brr::Mask mask_a, gpio2::B pin_a)
{
    return static_cast<gpio2::Brr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Brr::Value operator|(gpio2::Brr::Value left_a, gpio2::Brr::Value right_a)
{
    return static_cast<gpio2::Brr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Brr::Value operator&(gpio2::Brr::Value value_a, gpio2::Brr::Value mask_a)
{
    return static_cast<gpio2::Brr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
#endif
#if defined XMCU_GPIOC_PRESENT
template<> [[nodiscard]] constexpr gpio2::Port* gpio2::port<gpio2::C>()
{
    return reinterpret_cast<gpio2::Port*>(GPIOC_BASE);
}

template<> inline void gpio_clock2::enable<gpio2::C>()
{
    xmcu::bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIOCEN);
}
template<> inline void gpio_clock2::disable<gpio2::C>()
{
    xmcu::bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIOCEN);
}
template<> inline bool gpio_clock2::is_enabled<gpio2::C>()
{
    return xmcu::bit::flag::is(RCC->IOPENR, RCC_IOPENR_GPIOCEN);
}

template<> template<> void gpio2::WRC_reg<moder_descriptor>::toggle<gpio2::C>(gpio2::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), moder_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<moder_descriptor>::Value gpio2::WRC_reg<moder_descriptor>::get<gpio2::C>(gpio2::C pin_a) const
{
    return static_cast<gpio2::WRC_reg<moder_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier) & moder_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<otyper_descriptor>::toggle<gpio2::C>(gpio2::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            otyper_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<otyper_descriptor>::Value gpio2::WRC_reg<otyper_descriptor>::get<gpio2::C>(gpio2::C pin_a) const
{
    return static_cast<gpio2::WRC_reg<otyper_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier) & otyper_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<ospeedr_descriptor>::toggle<gpio2::C>(gpio2::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            ospeedr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<ospeedr_descriptor>::Value gpio2::WRC_reg<ospeedr_descriptor>::get<gpio2::C>(gpio2::C pin_a) const
{
    return static_cast<gpio2::WRC_reg<ospeedr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier) & ospeedr_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<pupdr_descriptor>::toggle<gpio2::C>(gpio2::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), pupdr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<pupdr_descriptor>::Value gpio2::WRC_reg<pupdr_descriptor>::get<gpio2::C>(gpio2::C pin_a) const
{
    return static_cast<gpio2::WRC_reg<pupdr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & pupdr_descriptor::mask);
}

template<> template<> gpio2::R_reg<idr_descriptor>::Value gpio2::R_reg<idr_descriptor>::get<gpio2::C>(gpio2::C pin_a) const
{
    return static_cast<gpio2::R_reg<idr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & idr_descriptor::mask);
}

template<> template<> void gpio2::WC_reg<odr_descriptor>::toggle<gpio2::C>(gpio2::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), odr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier));
}

template<> template<> void gpio2::WC_reg<bsrr_descriptor>::toggle<gpio2::C>(gpio2::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), bsrr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * bsrr_descriptor::shift_multiplier));
}

template<> template<> void gpio2::WRC_reg<afr_descriptor>::toggle<gpio2::C>(gpio2::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<afr_descriptor>::Value gpio2::WRC_reg<afr_descriptor>::get<gpio2::C>(gpio2::C pin_a) const
{
    return static_cast<gpio2::WRC_reg<afr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier) & afr_descriptor::mask);
}

template<> template<> void gpio2::WC_reg<brr_descriptor>::toggle<gpio2::C>(gpio2::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}

constexpr gpio2::Moder::Value operator<<(gpio2::Moder::Flag flag_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Moder::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio2::Moder::Value operator<<(gpio2::Moder::Mask mask_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Moder::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio2::Moder::Value operator|(gpio2::Moder::Value left_a, gpio2::Moder::Value right_a)
{
    return static_cast<gpio2::Moder::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Moder::Value operator&(gpio2::Moder::Value value_a, gpio2::Moder::Value mask_a)
{
    return static_cast<gpio2::Moder::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Otyper::Value operator<<(gpio2::Otyper::Flag flag_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Otyper::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio2::Otyper::Value operator<<(gpio2::Otyper::Mask mask_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Otyper::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio2::Otyper::Value operator|(gpio2::Otyper::Value left_a, gpio2::Otyper::Value right_a)
{
    return static_cast<gpio2::Otyper::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Otyper::Value operator&(gpio2::Otyper::Value value_a, gpio2::Otyper::Value mask_a)
{
    return static_cast<gpio2::Otyper::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Ospeedr::Value operator<<(gpio2::Ospeedr::Flag flag_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Ospeedr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio2::Ospeedr::Value operator<<(gpio2::Ospeedr::Mask mask_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Ospeedr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio2::Ospeedr::Value operator|(gpio2::Ospeedr::Value left_a, gpio2::Otyper::Value right_a)
{
    return static_cast<gpio2::Ospeedr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Ospeedr::Value operator&(gpio2::Ospeedr::Value value_a, gpio2::Ospeedr::Value mask_a)
{
    return static_cast<gpio2::Ospeedr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Pupdr::Value operator<<(gpio2::Pupdr::Flag flag_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Pupdr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio2::Pupdr::Value operator<<(gpio2::Pupdr::Mask mask_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Pupdr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio2::Pupdr::Value operator|(gpio2::Pupdr::Value left_a, gpio2::Pupdr::Value right_a)
{
    return static_cast<gpio2::Pupdr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Pupdr::Value operator&(gpio2::Pupdr::Value value_a, gpio2::Pupdr::Value mask_a)
{
    return static_cast<gpio2::Pupdr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Idr::Value operator<<(gpio2::Idr::Flag flag_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Idr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio2::Idr::Value operator<<(gpio2::Idr::Mask mask_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Idr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio2::Idr::Value operator|(gpio2::Idr::Value left_a, gpio2::Idr::Value right_a)
{
    return static_cast<gpio2::Idr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Idr::Value operator&(gpio2::Idr::Value value_a, gpio2::Idr::Value mask_a)
{
    return static_cast<gpio2::Idr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Odr::Value operator<<(gpio2::Odr::Flag flag_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Odr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Odr::Value operator<<(gpio2::Odr::Mask mask_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Odr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Odr::Value operator|(gpio2::Odr::Value left_a, gpio2::Odr::Value right_a)
{
    return static_cast<gpio2::Odr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Odr::Value operator&(gpio2::Odr::Value value_a, gpio2::Odr::Value mask_a)
{
    return static_cast<gpio2::Odr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Bsrr::Value operator<<(gpio2::Bsrr::Flag flag_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Bsrr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Bsrr::Value operator<<(gpio2::Bsrr::Mask mask_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Bsrr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Bsrr::Value operator|(gpio2::Bsrr::Value left_a, gpio2::Bsrr::Value right_a)
{
    return static_cast<gpio2::Bsrr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Bsrr::Value operator&(gpio2::Bsrr::Value value_a, gpio2::Bsrr::Value mask_a)
{
    return static_cast<gpio2::Bsrr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Lckr::Value operator<<(gpio2::Lckr::Flag flag_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Lckr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Value left_a, gpio2::Lckr::Value right_a)
{
    return static_cast<gpio2::Lckr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Flag flag_a, gpio2::Lckr::Value mask_a)
{
    assert(flag_a == gpio2::Lckr::key);
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(flag_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Value mask_a, gpio2::Lckr::Flag flag_a)
{
    assert(flag_a == gpio2::Lckr::key);
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(flag_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio2::Lckr::Value operator&(gpio2::Lckr::Value value_a, gpio2::Lckr::Value mask_a)
{
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Afr::Value operator<<(gpio2::Afr::Flag flag_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Afr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Afr::Value operator<<(gpio2::Afr::Mask mask_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Afr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Afr::Value operator|(gpio2::Afr::Value left_a, gpio2::Afr::Value right_a)
{
    return static_cast<gpio2::Afr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Afr::Value operator&(gpio2::Afr::Value value_a, gpio2::Afr::Value mask_a)
{
    return static_cast<gpio2::Afr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Brr::Value operator<<(gpio2::Brr::Flag flag_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Brr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Brr::Value operator<<(gpio2::Brr::Mask mask_a, gpio2::C pin_a)
{
    return static_cast<gpio2::Brr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Brr::Value operator|(gpio2::Brr::Value left_a, gpio2::Brr::Value right_a)
{
    return static_cast<gpio2::Brr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Brr::Value operator&(gpio2::Brr::Value value_a, gpio2::Brr::Value mask_a)
{
    return static_cast<gpio2::Brr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
#endif
#if defined XMCU_GPIOD_PRESENT
template<> [[nodiscard]] constexpr gpio2::Port* gpio2::port<gpio2::D>()
{
    return reinterpret_cast<gpio2::Port*>(GPIOD_BASE);
}

template<> inline void gpio_clock2::enable<gpio2::D>()
{
    xmcu::bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIODEN);
}
template<> inline void gpio_clock2::disable<gpio2::D>()
{
    xmcu::bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIODEN);
}
template<> inline bool gpio_clock2::is_enabled<gpio2::D>()
{
    return xmcu::bit::flag::is(RCC->IOPENR, RCC_IOPENR_GPIODEN);
}

template<> template<> void gpio2::WRC_reg<moder_descriptor>::toggle<gpio2::D>(gpio2::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), moder_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<moder_descriptor>::Value gpio2::WRC_reg<moder_descriptor>::get<gpio2::D>(gpio2::D pin_a) const
{
    return static_cast<gpio2::WRC_reg<moder_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier) & moder_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<otyper_descriptor>::toggle<gpio2::D>(gpio2::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            otyper_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<otyper_descriptor>::Value gpio2::WRC_reg<otyper_descriptor>::get<gpio2::D>(gpio2::D pin_a) const
{
    return static_cast<gpio2::WRC_reg<otyper_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier) & otyper_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<ospeedr_descriptor>::toggle<gpio2::D>(gpio2::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            ospeedr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<ospeedr_descriptor>::Value gpio2::WRC_reg<ospeedr_descriptor>::get<gpio2::D>(gpio2::D pin_a) const
{
    return static_cast<gpio2::WRC_reg<ospeedr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier) & ospeedr_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<pupdr_descriptor>::toggle<gpio2::D>(gpio2::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), pupdr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<pupdr_descriptor>::Value gpio2::WRC_reg<pupdr_descriptor>::get<gpio2::D>(gpio2::D pin_a) const
{
    return static_cast<gpio2::WRC_reg<pupdr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & pupdr_descriptor::mask);
}

template<> template<> gpio2::R_reg<idr_descriptor>::Value gpio2::R_reg<idr_descriptor>::get<gpio2::D>(gpio2::D pin_a) const
{
    return static_cast<gpio2::R_reg<idr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & idr_descriptor::mask);
}

template<> template<> void gpio2::WC_reg<odr_descriptor>::toggle<gpio2::D>(gpio2::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), odr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier));
}

template<> template<> void gpio2::WC_reg<bsrr_descriptor>::toggle<gpio2::D>(gpio2::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), bsrr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * bsrr_descriptor::shift_multiplier));
}

template<> template<> void gpio2::WRC_reg<afr_descriptor>::toggle<gpio2::D>(gpio2::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<afr_descriptor>::Value gpio2::WRC_reg<afr_descriptor>::get<gpio2::D>(gpio2::D pin_a) const
{
    return static_cast<gpio2::WRC_reg<afr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier) & afr_descriptor::mask);
}

template<> template<> void gpio2::WC_reg<brr_descriptor>::toggle<gpio2::D>(gpio2::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}

constexpr gpio2::Moder::Value operator<<(gpio2::Moder::Flag flag_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Moder::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio2::Moder::Value operator<<(gpio2::Moder::Mask mask_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Moder::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio2::Moder::Value operator|(gpio2::Moder::Value left_a, gpio2::Moder::Value right_a)
{
    return static_cast<gpio2::Moder::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Moder::Value operator&(gpio2::Moder::Value value_a, gpio2::Moder::Value mask_a)
{
    return static_cast<gpio2::Moder::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Otyper::Value operator<<(gpio2::Otyper::Flag flag_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Otyper::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio2::Otyper::Value operator<<(gpio2::Otyper::Mask mask_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Otyper::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio2::Otyper::Value operator|(gpio2::Otyper::Value left_a, gpio2::Otyper::Value right_a)
{
    return static_cast<gpio2::Otyper::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Otyper::Value operator&(gpio2::Otyper::Value value_a, gpio2::Otyper::Value mask_a)
{
    return static_cast<gpio2::Otyper::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Ospeedr::Value operator<<(gpio2::Ospeedr::Flag flag_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Ospeedr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio2::Ospeedr::Value operator<<(gpio2::Ospeedr::Mask mask_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Ospeedr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio2::Ospeedr::Value operator|(gpio2::Ospeedr::Value left_a, gpio2::Otyper::Value right_a)
{
    return static_cast<gpio2::Ospeedr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Ospeedr::Value operator&(gpio2::Ospeedr::Value value_a, gpio2::Ospeedr::Value mask_a)
{
    return static_cast<gpio2::Ospeedr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Pupdr::Value operator<<(gpio2::Pupdr::Flag flag_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Pupdr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio2::Pupdr::Value operator<<(gpio2::Pupdr::Mask mask_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Pupdr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio2::Pupdr::Value operator|(gpio2::Pupdr::Value left_a, gpio2::Pupdr::Value right_a)
{
    return static_cast<gpio2::Pupdr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Pupdr::Value operator&(gpio2::Pupdr::Value value_a, gpio2::Pupdr::Value mask_a)
{
    return static_cast<gpio2::Pupdr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Idr::Value operator<<(gpio2::Idr::Flag flag_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Idr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio2::Idr::Value operator<<(gpio2::Idr::Mask mask_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Idr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio2::Idr::Value operator|(gpio2::Idr::Value left_a, gpio2::Idr::Value right_a)
{
    return static_cast<gpio2::Idr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Idr::Value operator&(gpio2::Idr::Value value_a, gpio2::Idr::Value mask_a)
{
    return static_cast<gpio2::Idr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Odr::Value operator<<(gpio2::Odr::Flag flag_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Odr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Odr::Value operator<<(gpio2::Odr::Mask mask_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Odr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Odr::Value operator|(gpio2::Odr::Value left_a, gpio2::Odr::Value right_a)
{
    return static_cast<gpio2::Odr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Odr::Value operator&(gpio2::Odr::Value value_a, gpio2::Odr::Value mask_a)
{
    return static_cast<gpio2::Odr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Bsrr::Value operator<<(gpio2::Bsrr::Flag flag_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Bsrr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Bsrr::Value operator<<(gpio2::Bsrr::Mask mask_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Bsrr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Bsrr::Value operator|(gpio2::Bsrr::Value left_a, gpio2::Bsrr::Value right_a)
{
    return static_cast<gpio2::Bsrr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Bsrr::Value operator&(gpio2::Bsrr::Value value_a, gpio2::Bsrr::Value mask_a)
{
    return static_cast<gpio2::Bsrr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Lckr::Value operator<<(gpio2::Lckr::Flag flag_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Lckr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Value left_a, gpio2::Lckr::Value right_a)
{
    return static_cast<gpio2::Lckr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Flag flag_a, gpio2::Lckr::Value mask_a)
{
    assert(flag_a == gpio2::Lckr::key);
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(flag_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Value mask_a, gpio2::Lckr::Flag flag_a)
{
    assert(flag_a == gpio2::Lckr::key);
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(flag_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio2::Lckr::Value operator&(gpio2::Lckr::Value value_a, gpio2::Lckr::Value mask_a)
{
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Afr::Value operator<<(gpio2::Afr::Flag flag_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Afr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Afr::Value operator<<(gpio2::Afr::Mask mask_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Afr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Afr::Value operator|(gpio2::Afr::Value left_a, gpio2::Afr::Value right_a)
{
    return static_cast<gpio2::Afr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Afr::Value operator&(gpio2::Afr::Value value_a, gpio2::Afr::Value mask_a)
{
    return static_cast<gpio2::Afr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Brr::Value operator<<(gpio2::Brr::Flag flag_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Brr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Brr::Value operator<<(gpio2::Brr::Mask mask_a, gpio2::D pin_a)
{
    return static_cast<gpio2::Brr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Brr::Value operator|(gpio2::Brr::Value left_a, gpio2::Brr::Value right_a)
{
    return static_cast<gpio2::Brr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Brr::Value operator&(gpio2::Brr::Value value_a, gpio2::Brr::Value mask_a)
{
    return static_cast<gpio2::Brr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
#endif
#if defined XMCU_GPIOF_PRESENT
template<> [[nodiscard]] constexpr gpio2::Port* gpio2::port<gpio2::F>()
{
    return reinterpret_cast<gpio2::Port*>(GPIOF_BASE);
}

template<> inline void gpio_clock2::enable<gpio2::F>()
{
    xmcu::bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIOFEN);
}
template<> inline void gpio_clock2::disable<gpio2::F>()
{
    xmcu::bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIOFEN);
}
template<> inline bool gpio_clock2::is_enabled<gpio2::F>()
{
    return xmcu::bit::flag::is(RCC->IOPENR, RCC_IOPENR_GPIOFEN);
}

template<> template<> void gpio2::WRC_reg<moder_descriptor>::toggle<gpio2::F>(gpio2::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), moder_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<moder_descriptor>::Value gpio2::WRC_reg<moder_descriptor>::get<gpio2::F>(gpio2::F pin_a) const
{
    return static_cast<gpio2::WRC_reg<moder_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier) & moder_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<otyper_descriptor>::toggle<gpio2::F>(gpio2::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            otyper_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<otyper_descriptor>::Value gpio2::WRC_reg<otyper_descriptor>::get<gpio2::F>(gpio2::F pin_a) const
{
    return static_cast<gpio2::WRC_reg<otyper_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier) & otyper_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<ospeedr_descriptor>::toggle<gpio2::F>(gpio2::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            ospeedr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<ospeedr_descriptor>::Value gpio2::WRC_reg<ospeedr_descriptor>::get<gpio2::F>(gpio2::F pin_a) const
{
    return static_cast<gpio2::WRC_reg<ospeedr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier) & ospeedr_descriptor::mask);
}

template<> template<> void gpio2::WRC_reg<pupdr_descriptor>::toggle<gpio2::F>(gpio2::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), pupdr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<pupdr_descriptor>::Value gpio2::WRC_reg<pupdr_descriptor>::get<gpio2::F>(gpio2::F pin_a) const
{
    return static_cast<gpio2::WRC_reg<pupdr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & pupdr_descriptor::mask);
}

template<> template<> gpio2::R_reg<idr_descriptor>::Value gpio2::R_reg<idr_descriptor>::get<gpio2::F>(gpio2::F pin_a) const
{
    return static_cast<gpio2::R_reg<idr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & idr_descriptor::mask);
}

template<> template<> void gpio2::WC_reg<odr_descriptor>::toggle<gpio2::F>(gpio2::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), odr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier));
}

template<> template<> void gpio2::WC_reg<bsrr_descriptor>::toggle<gpio2::F>(gpio2::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), bsrr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * bsrr_descriptor::shift_multiplier));
}

template<> template<> void gpio2::WRC_reg<afr_descriptor>::toggle<gpio2::F>(gpio2::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}
template<> template<> gpio2::WRC_reg<afr_descriptor>::Value gpio2::WRC_reg<afr_descriptor>::get<gpio2::F>(gpio2::F pin_a) const
{
    return static_cast<gpio2::WRC_reg<afr_descriptor>::Value>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier) & afr_descriptor::mask);
}

template<> template<> void gpio2::WC_reg<brr_descriptor>::toggle<gpio2::F>(gpio2::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}

constexpr gpio2::Moder::Value operator<<(gpio2::Moder::Flag flag_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Moder::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio2::Moder::Value operator<<(gpio2::Moder::Mask mask_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Moder::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio2::Moder::Value operator|(gpio2::Moder::Value left_a, gpio2::Moder::Value right_a)
{
    return static_cast<gpio2::Moder::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Moder::Value operator&(gpio2::Moder::Value value_a, gpio2::Moder::Value mask_a)
{
    return static_cast<gpio2::Moder::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Otyper::Value operator<<(gpio2::Otyper::Flag flag_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Otyper::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio2::Otyper::Value operator<<(gpio2::Otyper::Mask mask_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Otyper::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio2::Otyper::Value operator|(gpio2::Otyper::Value left_a, gpio2::Otyper::Value right_a)
{
    return static_cast<gpio2::Otyper::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Otyper::Value operator&(gpio2::Otyper::Value value_a, gpio2::Otyper::Value mask_a)
{
    return static_cast<gpio2::Otyper::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Ospeedr::Value operator<<(gpio2::Ospeedr::Flag flag_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Ospeedr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio2::Ospeedr::Value operator<<(gpio2::Ospeedr::Mask mask_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Ospeedr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio2::Ospeedr::Value operator|(gpio2::Ospeedr::Value left_a, gpio2::Otyper::Value right_a)
{
    return static_cast<gpio2::Ospeedr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Ospeedr::Value operator&(gpio2::Ospeedr::Value value_a, gpio2::Ospeedr::Value mask_a)
{
    return static_cast<gpio2::Ospeedr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Pupdr::Value operator<<(gpio2::Pupdr::Flag flag_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Pupdr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio2::Pupdr::Value operator<<(gpio2::Pupdr::Mask mask_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Pupdr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio2::Pupdr::Value operator|(gpio2::Pupdr::Value left_a, gpio2::Pupdr::Value right_a)
{
    return static_cast<gpio2::Pupdr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Pupdr::Value operator&(gpio2::Pupdr::Value value_a, gpio2::Pupdr::Value mask_a)
{
    return static_cast<gpio2::Pupdr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Idr::Value operator<<(gpio2::Idr::Flag flag_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Idr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio2::Idr::Value operator<<(gpio2::Idr::Mask mask_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Idr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio2::Idr::Value operator|(gpio2::Idr::Value left_a, gpio2::Idr::Value right_a)
{
    return static_cast<gpio2::Idr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Idr::Value operator&(gpio2::Idr::Value value_a, gpio2::Idr::Value mask_a)
{
    return static_cast<gpio2::Idr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Odr::Value operator<<(gpio2::Odr::Flag flag_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Odr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Odr::Value operator<<(gpio2::Odr::Mask mask_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Odr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Odr::Value operator|(gpio2::Odr::Value left_a, gpio2::Odr::Value right_a)
{
    return static_cast<gpio2::Odr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Odr::Value operator&(gpio2::Odr::Value value_a, gpio2::Odr::Value mask_a)
{
    return static_cast<gpio2::Odr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Bsrr::Value operator<<(gpio2::Bsrr::Flag flag_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Bsrr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Bsrr::Value operator<<(gpio2::Bsrr::Mask mask_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Bsrr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Bsrr::Value operator|(gpio2::Bsrr::Value left_a, gpio2::Bsrr::Value right_a)
{
    return static_cast<gpio2::Bsrr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Bsrr::Value operator&(gpio2::Bsrr::Value value_a, gpio2::Bsrr::Value mask_a)
{
    return static_cast<gpio2::Bsrr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Lckr::Value operator<<(gpio2::Lckr::Flag flag_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Lckr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Value left_a, gpio2::Lckr::Value right_a)
{
    return static_cast<gpio2::Lckr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Flag flag_a, gpio2::Lckr::Value mask_a)
{
    assert(flag_a == gpio2::Lckr::key);
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(flag_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio2::Lckr::Value operator|(gpio2::Lckr::Value mask_a, gpio2::Lckr::Flag flag_a)
{
    assert(flag_a == gpio2::Lckr::key);
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(flag_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio2::Lckr::Value operator&(gpio2::Lckr::Value value_a, gpio2::Lckr::Value mask_a)
{
    return static_cast<gpio2::Lckr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Afr::Value operator<<(gpio2::Afr::Flag flag_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Afr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Afr::Value operator<<(gpio2::Afr::Mask mask_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Afr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Afr::Value operator|(gpio2::Afr::Value left_a, gpio2::Afr::Value right_a)
{
    return static_cast<gpio2::Afr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Afr::Value operator&(gpio2::Afr::Value value_a, gpio2::Afr::Value mask_a)
{
    return static_cast<gpio2::Afr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio2::Brr::Value operator<<(gpio2::Brr::Flag flag_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Brr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Brr::Value operator<<(gpio2::Brr::Mask mask_a, gpio2::F pin_a)
{
    return static_cast<gpio2::Brr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio2::Brr::Value operator|(gpio2::Brr::Value left_a, gpio2::Brr::Value right_a)
{
    return static_cast<gpio2::Brr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio2::Brr::Value operator&(gpio2::Brr::Value value_a, gpio2::Brr::Value mask_a)
{
    return static_cast<gpio2::Brr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}
#endif
} // namespace soc::st::arm::m0::u0::rm0503::peripherals::ll
