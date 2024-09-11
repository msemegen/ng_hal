#pragma once

/*
 *	Name: gpio_ll.hpp
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

    enum class Mask : std::uint32_t
    {
        mask = mask
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

        template<typename Pin_t> Flag get(Pin_t pin_a) const = delete;
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

        template<typename Pin_t> Flag get(Pin_t pin_a) const = delete;
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

        template<typename Pin_t> Flag get(Pin_t pin_a) const = delete;
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

public:
    struct Moder : public WRC_reg<moder_descriptor>
    {
        using enum moder_descriptor::Flag;
        using enum moder_descriptor::Mask;
        using Value = WRC_reg<moder_descriptor>::Value;
    };
    struct Otyper : public WRC_reg<otyper_descriptor>
    {
        using enum otyper_descriptor::Flag;
        using enum otyper_descriptor::Mask;
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

template<> template<>
inline void gpio::WRC_reg<moder_descriptor>::toggle<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), moder_descriptor::mask << (pin_a * moder_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<moder_descriptor>::Flag
gpio::WRC_reg<moder_descriptor>::get<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a) const
{
    return static_cast<gpio::WRC_reg<moder_descriptor>::Flag>(this->v >> (pin_a * moder_descriptor::shift_multiplier) &
                                                              moder_descriptor::mask);
}

template<> template<>
inline void gpio::WRC_reg<otyper_descriptor>::toggle<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), otyper_descriptor::mask << (pin_a * otyper_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<otyper_descriptor>::Flag
gpio::WRC_reg<otyper_descriptor>::get<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a) const
{
    return static_cast<gpio::WRC_reg<otyper_descriptor>::Flag>(this->v >> (pin_a * otyper_descriptor::shift_multiplier) &
                                                               otyper_descriptor::mask);
}

template<> template<>
inline void gpio::WRC_reg<ospeedr_descriptor>::toggle<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), ospeedr_descriptor::mask << (pin_a * ospeedr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<ospeedr_descriptor>::Flag
gpio::WRC_reg<ospeedr_descriptor>::get<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a) const
{
    return static_cast<gpio::WRC_reg<ospeedr_descriptor>::Flag>(this->v >> (pin_a * ospeedr_descriptor::shift_multiplier) &
                                                                ospeedr_descriptor::mask);
}

template<> template<>
inline void gpio::WRC_reg<pupdr_descriptor>::toggle<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), pupdr_descriptor::mask << (pin_a * pupdr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<pupdr_descriptor>::Flag
gpio::WRC_reg<pupdr_descriptor>::get<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a) const
{
    return static_cast<gpio::WRC_reg<pupdr_descriptor>::Flag>(this->v >> (pin_a * pupdr_descriptor::shift_multiplier) &
                                                              pupdr_descriptor::mask);
}

template<> template<> inline gpio::R_reg<idr_descriptor>::Flag
gpio::R_reg<idr_descriptor>::get<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a) const
{
    return static_cast<gpio::R_reg<idr_descriptor>::Flag>(this->v >> (pin_a * pupdr_descriptor::shift_multiplier) & idr_descriptor::mask);
}

template<> template<>
inline void gpio::WC_reg<odr_descriptor>::toggle<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), odr_descriptor::mask << (pin_a * odr_descriptor::shift_multiplier));
}

template<> template<>
inline void gpio::WC_reg<bsrr_descriptor>::toggle<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), bsrr_descriptor::mask << (pin_a * bsrr_descriptor::shift_multiplier));
}

template<> template<> inline gpio::WRC_reg<lckr_descriptor>::Flag
gpio::WRC_reg<lckr_descriptor>::get<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a) const
{
    return static_cast<gpio::WRC_reg<lckr_descriptor>::Flag>(this->v >> (pin_a * pupdr_descriptor::shift_multiplier) &
                                                             lckr_descriptor::mask);
}

template<> template<>
inline void gpio::WRC_reg<afr_descriptor>::toggle<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (pin_a * afr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<afr_descriptor>::Flag
gpio::WRC_reg<afr_descriptor>::get<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a) const
{
    return static_cast<gpio::WRC_reg<afr_descriptor>::Flag>(this->v >> (pin_a * afr_descriptor::shift_multiplier) & afr_descriptor::mask);
}

template<> template<>
inline void gpio::WC_reg<brr_descriptor>::toggle<xmcu::Limited<std::uint32_t, 0u, 15u>>(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (pin_a * afr_descriptor::shift_multiplier));
}

constexpr gpio::Moder::Value operator<<(gpio::Moder::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Moder::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * moder_descriptor::shift_multiplier));
}
constexpr gpio::Moder::Value operator<<(gpio::Moder::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Moder::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * moder_descriptor::shift_multiplier));
}

constexpr gpio::Otyper::Value operator<<(gpio::Otyper::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Otyper::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * otyper_descriptor::shift_multiplier));
}
constexpr gpio::Otyper::Value operator<<(gpio::Otyper::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Otyper::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * otyper_descriptor::shift_multiplier));
}

constexpr gpio::Ospeedr::Value operator<<(gpio::Ospeedr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Ospeedr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * ospeedr_descriptor::shift_multiplier));
}
constexpr gpio::Ospeedr::Value operator<<(gpio::Ospeedr::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Ospeedr::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * ospeedr_descriptor::shift_multiplier));
}

constexpr gpio::Pupdr::Value operator<<(gpio::Pupdr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Pupdr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * pupdr_descriptor::shift_multiplier));
}
constexpr gpio::Pupdr::Value operator<<(gpio::Pupdr::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Pupdr::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * pupdr_descriptor::shift_multiplier));
}

constexpr gpio::Idr::Value operator<<(gpio::Idr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Idr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * idr_descriptor::shift_multiplier));
}
constexpr gpio::Idr::Value operator<<(gpio::Idr::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Idr::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * idr_descriptor::shift_multiplier));
}

constexpr gpio::Odr::Value operator<<(gpio::Odr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Odr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * odr_descriptor::shift_multiplier));
}
constexpr gpio::Odr::Value operator<<(gpio::Odr::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Odr::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * odr_descriptor::shift_multiplier));
}

constexpr gpio::Bsrr::Value operator<<(gpio::Bsrr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Bsrr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * odr_descriptor::shift_multiplier));
}
constexpr gpio::Bsrr::Value operator<<(gpio::Bsrr::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Bsrr::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * odr_descriptor::shift_multiplier));
}

constexpr gpio::Lckr::Value operator<<(gpio::Lckr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Lckr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * lckr_descriptor::shift_multiplier));
}

constexpr gpio::Afr::Value operator<<(gpio::Afr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Afr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * afr_descriptor::shift_multiplier));
}
constexpr gpio::Afr::Value operator<<(gpio::Afr::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Afr::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * odr_descriptor::shift_multiplier));
}

constexpr gpio::Brr::Value operator<<(gpio::Brr::Flag flag_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Brr::Value>(static_cast<std::uint32_t>(flag_a) << (pin_a * afr_descriptor::shift_multiplier));
}
constexpr gpio::Brr::Value operator<<(gpio::Brr::Mask mask_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
{
    return static_cast<gpio::Brr::Value>(static_cast<std::uint32_t>(mask_a) << (pin_a * odr_descriptor::shift_multiplier));
}

constexpr gpio::Moder::Value operator|(gpio::Moder::Value left_a, gpio::Moder::Value right_a)
{
    return static_cast<gpio::Moder::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::Moder::Value operator&(gpio::Moder::Value value_a, gpio::Moder::Value mask_a)
{
    return static_cast<gpio::Moder::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio::Otyper::Value operator|(gpio::Otyper::Value left_a, gpio::Otyper::Value right_a)
{
    return static_cast<gpio::Otyper::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::Otyper::Value operator&(gpio::Otyper::Value value_a, gpio::Otyper::Value mask_a)
{
    return static_cast<gpio::Otyper::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio::Ospeedr::Value operator|(gpio::Ospeedr::Value left_a, gpio::Otyper::Value right_a)
{
    return static_cast<gpio::Ospeedr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::Ospeedr::Value operator&(gpio::Ospeedr::Value value_a, gpio::Ospeedr::Value mask_a)
{
    return static_cast<gpio::Ospeedr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio::Pupdr::Value operator|(gpio::Pupdr::Value left_a, gpio::Pupdr::Value right_a)
{
    return static_cast<gpio::Pupdr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::Pupdr::Value operator&(gpio::Pupdr::Value value_a, gpio::Pupdr::Value mask_a)
{
    return static_cast<gpio::Pupdr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio::Idr::Value operator|(gpio::Idr::Value left_a, gpio::Idr::Value right_a)
{
    return static_cast<gpio::Idr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::Idr::Value operator&(gpio::Idr::Value value_a, gpio::Idr::Value mask_a)
{
    return static_cast<gpio::Idr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio::Odr::Value operator|(gpio::Odr::Value left_a, gpio::Odr::Value right_a)
{
    return static_cast<gpio::Odr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::Odr::Value operator&(gpio::Odr::Value value_a, gpio::Odr::Value mask_a)
{
    return static_cast<gpio::Odr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio::Bsrr::Value operator|(gpio::Bsrr::Value left_a, gpio::Bsrr::Value right_a)
{
    return static_cast<gpio::Bsrr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::Bsrr::Value operator&(gpio::Bsrr::Value value_a, gpio::Bsrr::Value mask_a)
{
    return static_cast<gpio::Bsrr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio::Lckr::Value operator|(gpio::Lckr::Value left_a, gpio::Lckr::Value right_a)
{
    return static_cast<gpio::Lckr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::Lckr::Value operator|(gpio::Lckr::Flag flag_a, gpio::Lckr::Value mask_a)
{
    assert(flag_a == gpio::Lckr::key);
    return static_cast<gpio::Lckr::Value>((static_cast<std::uint32_t>(flag_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio::Lckr::Value operator|(gpio::Lckr::Value mask_a, gpio::Lckr::Flag flag_a)
{
    assert(flag_a == gpio::Lckr::key);
    return static_cast<gpio::Lckr::Value>((static_cast<std::uint32_t>(flag_a) & static_cast<std::uint32_t>(mask_a)));
}
constexpr gpio::Lckr::Value operator&(gpio::Lckr::Value value_a, gpio::Lckr::Value mask_a)
{
    return static_cast<gpio::Lckr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio::Afr::Value operator|(gpio::Afr::Value left_a, gpio::Afr::Value right_a)
{
    return static_cast<gpio::Afr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::Afr::Value operator&(gpio::Afr::Value value_a, gpio::Afr::Value mask_a)
{
    return static_cast<gpio::Afr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

constexpr gpio::Brr::Value operator|(gpio::Brr::Value left_a, gpio::Brr::Value right_a)
{
    return static_cast<gpio::Brr::Value>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::Brr::Value operator&(gpio::Brr::Value value_a, gpio::Brr::Value mask_a)
{
    return static_cast<gpio::Brr::Value>((static_cast<std::uint32_t>(value_a) & static_cast<std::uint32_t>(mask_a)));
}

#if defined XMCU_GPIOA_PRESENT
template<> [[nodiscard]] constexpr gpio::Port* gpio::port<gpio::A>()
{
    return reinterpret_cast<gpio::Port*>(GPIOA_BASE);
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

template<> template<> inline void gpio::WRC_reg<moder_descriptor>::toggle<gpio::A>(gpio::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), moder_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<moder_descriptor>::Flag gpio::WRC_reg<moder_descriptor>::get<gpio::A>(gpio::A pin_a) const
{
    return static_cast<gpio::WRC_reg<moder_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier) & moder_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<otyper_descriptor>::toggle<gpio::A>(gpio::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            otyper_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<otyper_descriptor>::Flag gpio::WRC_reg<otyper_descriptor>::get<gpio::A>(gpio::A pin_a) const
{
    return static_cast<gpio::WRC_reg<otyper_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier) & otyper_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<ospeedr_descriptor>::toggle<gpio::A>(gpio::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            ospeedr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<ospeedr_descriptor>::Flag gpio::WRC_reg<ospeedr_descriptor>::get<gpio::A>(gpio::A pin_a) const
{
    return static_cast<gpio::WRC_reg<ospeedr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier) & ospeedr_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<pupdr_descriptor>::toggle<gpio::A>(gpio::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), pupdr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<pupdr_descriptor>::Flag gpio::WRC_reg<pupdr_descriptor>::get<gpio::A>(gpio::A pin_a) const
{
    return static_cast<gpio::WRC_reg<pupdr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & pupdr_descriptor::mask);
}

template<> template<> inline gpio::R_reg<idr_descriptor>::Flag gpio::R_reg<idr_descriptor>::get<gpio::A>(gpio::A pin_a) const
{
    return static_cast<gpio::R_reg<idr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & idr_descriptor::mask);
}

template<> template<> inline void gpio::WC_reg<odr_descriptor>::toggle<gpio::A>(gpio::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), odr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier));
}

template<> template<> inline void gpio::WC_reg<bsrr_descriptor>::toggle<gpio::A>(gpio::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), bsrr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * bsrr_descriptor::shift_multiplier));
}

template<> template<> inline void gpio::WRC_reg<afr_descriptor>::toggle<gpio::A>(gpio::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<afr_descriptor>::Flag gpio::WRC_reg<afr_descriptor>::get<gpio::A>(gpio::A pin_a) const
{
    return static_cast<gpio::WRC_reg<afr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier) & afr_descriptor::mask);
}

template<> template<> inline gpio::WRC_reg<lckr_descriptor>::Flag gpio::WRC_reg<lckr_descriptor>::get<gpio::A>(gpio::A pin_a) const
{
    return static_cast<gpio::WRC_reg<lckr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & lckr_descriptor::mask);
}

template<> template<> inline void gpio::WC_reg<brr_descriptor>::toggle<gpio::A>(gpio::A pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}

constexpr gpio::Moder::Value operator<<(gpio::Moder::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::Moder::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio::Moder::Value operator<<(gpio::Moder::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::Moder::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}

constexpr gpio::Otyper::Value operator<<(gpio::Otyper::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::Otyper::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio::Otyper::Value operator<<(gpio::Otyper::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::Otyper::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}

constexpr gpio::Ospeedr::Value operator<<(gpio::Ospeedr::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::Ospeedr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio::Ospeedr::Value operator<<(gpio::Ospeedr::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::Ospeedr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}

constexpr gpio::Pupdr::Value operator<<(gpio::Pupdr::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::Pupdr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio::Pupdr::Value operator<<(gpio::Pupdr::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::Pupdr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}

constexpr gpio::Idr::Value operator<<(gpio::Idr::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::Idr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio::Idr::Value operator<<(gpio::Idr::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::Idr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}

constexpr gpio::Odr::Value operator<<(gpio::Odr::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::Odr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio::Odr::Value operator<<(gpio::Odr::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::Odr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Bsrr::Value operator<<(gpio::Bsrr::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::Bsrr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio::Bsrr::Value operator<<(gpio::Bsrr::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::Bsrr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Lckr::Value operator<<(gpio::Lckr::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::Lckr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Afr::Value operator<<(gpio::Afr::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::Afr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio::Afr::Value operator<<(gpio::Afr::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::Afr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}

constexpr gpio::Brr::Value operator<<(gpio::Brr::Flag flag_a, gpio::A pin_a)
{
    return static_cast<gpio::Brr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio::Brr::Value operator<<(gpio::Brr::Mask mask_a, gpio::A pin_a)
{
    return static_cast<gpio::Brr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
#endif
#if defined XMCU_GPIOB_PRESENT
template<> [[nodiscard]] constexpr gpio::Port* gpio::port<gpio::B>()
{
    return reinterpret_cast<gpio::Port*>(GPIOB_BASE);
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

template<> template<> inline void gpio::WRC_reg<moder_descriptor>::toggle<gpio::B>(gpio::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), moder_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<moder_descriptor>::Flag gpio::WRC_reg<moder_descriptor>::get<gpio::B>(gpio::B pin_a) const
{
    return static_cast<gpio::WRC_reg<moder_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier) & moder_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<otyper_descriptor>::toggle<gpio::B>(gpio::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            otyper_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<otyper_descriptor>::Flag gpio::WRC_reg<otyper_descriptor>::get<gpio::B>(gpio::B pin_a) const
{
    return static_cast<gpio::WRC_reg<otyper_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier) & otyper_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<ospeedr_descriptor>::toggle<gpio::B>(gpio::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            ospeedr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<ospeedr_descriptor>::Flag gpio::WRC_reg<ospeedr_descriptor>::get<gpio::B>(gpio::B pin_a) const
{
    return static_cast<gpio::WRC_reg<ospeedr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier) & ospeedr_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<pupdr_descriptor>::toggle<gpio::B>(gpio::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), pupdr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<pupdr_descriptor>::Flag gpio::WRC_reg<pupdr_descriptor>::get<gpio::B>(gpio::B pin_a) const
{
    return static_cast<gpio::WRC_reg<pupdr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & pupdr_descriptor::mask);
}

template<> template<> inline gpio::R_reg<idr_descriptor>::Flag gpio::R_reg<idr_descriptor>::get<gpio::B>(gpio::B pin_a) const
{
    return static_cast<gpio::R_reg<idr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & idr_descriptor::mask);
}

template<> template<> inline void gpio::WC_reg<odr_descriptor>::toggle<gpio::B>(gpio::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), odr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier));
}

template<> template<> inline void gpio::WC_reg<bsrr_descriptor>::toggle<gpio::B>(gpio::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), bsrr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * bsrr_descriptor::shift_multiplier));
}

template<> template<> inline gpio::WRC_reg<lckr_descriptor>::Flag gpio::WRC_reg<lckr_descriptor>::get<gpio::B>(gpio::B pin_a) const
{
    return static_cast<gpio::WRC_reg<lckr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & lckr_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<afr_descriptor>::toggle<gpio::B>(gpio::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<afr_descriptor>::Flag gpio::WRC_reg<afr_descriptor>::get<gpio::B>(gpio::B pin_a) const
{
    return static_cast<gpio::WRC_reg<afr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier) & afr_descriptor::mask);
}

template<> template<> inline void gpio::WC_reg<brr_descriptor>::toggle<gpio::B>(gpio::B pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}

constexpr gpio::Moder::Value operator<<(gpio::Moder::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::Moder::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio::Moder::Value operator<<(gpio::Moder::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::Moder::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}

constexpr gpio::Otyper::Value operator<<(gpio::Otyper::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::Otyper::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio::Otyper::Value operator<<(gpio::Otyper::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::Otyper::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}

constexpr gpio::Ospeedr::Value operator<<(gpio::Ospeedr::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::Ospeedr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio::Ospeedr::Value operator<<(gpio::Ospeedr::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::Ospeedr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}

constexpr gpio::Pupdr::Value operator<<(gpio::Pupdr::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::Pupdr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio::Pupdr::Value operator<<(gpio::Pupdr::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::Pupdr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}

constexpr gpio::Idr::Value operator<<(gpio::Idr::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::Idr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio::Idr::Value operator<<(gpio::Idr::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::Idr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}

constexpr gpio::Odr::Value operator<<(gpio::Odr::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::Odr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio::Odr::Value operator<<(gpio::Odr::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::Odr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Bsrr::Value operator<<(gpio::Bsrr::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::Bsrr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio::Bsrr::Value operator<<(gpio::Bsrr::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::Bsrr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Lckr::Value operator<<(gpio::Lckr::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::Lckr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Afr::Value operator<<(gpio::Afr::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::Afr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio::Afr::Value operator<<(gpio::Afr::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::Afr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}

constexpr gpio::Brr::Value operator<<(gpio::Brr::Flag flag_a, gpio::B pin_a)
{
    return static_cast<gpio::Brr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio::Brr::Value operator<<(gpio::Brr::Mask mask_a, gpio::B pin_a)
{
    return static_cast<gpio::Brr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
#endif
#if defined XMCU_GPIOC_PRESENT
template<> [[nodiscard]] constexpr gpio::Port* gpio::port<gpio::C>()
{
    return reinterpret_cast<gpio::Port*>(GPIOC_BASE);
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

template<> template<> inline void gpio::WRC_reg<moder_descriptor>::toggle<gpio::C>(gpio::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), moder_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<moder_descriptor>::Flag gpio::WRC_reg<moder_descriptor>::get<gpio::C>(gpio::C pin_a) const
{
    return static_cast<gpio::WRC_reg<moder_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier) & moder_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<otyper_descriptor>::toggle<gpio::C>(gpio::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            otyper_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<otyper_descriptor>::Flag gpio::WRC_reg<otyper_descriptor>::get<gpio::C>(gpio::C pin_a) const
{
    return static_cast<gpio::WRC_reg<otyper_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier) & otyper_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<ospeedr_descriptor>::toggle<gpio::C>(gpio::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            ospeedr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<ospeedr_descriptor>::Flag gpio::WRC_reg<ospeedr_descriptor>::get<gpio::C>(gpio::C pin_a) const
{
    return static_cast<gpio::WRC_reg<ospeedr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier) & ospeedr_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<pupdr_descriptor>::toggle<gpio::C>(gpio::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), pupdr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<pupdr_descriptor>::Flag gpio::WRC_reg<pupdr_descriptor>::get<gpio::C>(gpio::C pin_a) const
{
    return static_cast<gpio::WRC_reg<pupdr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & pupdr_descriptor::mask);
}

template<> template<> inline gpio::R_reg<idr_descriptor>::Flag gpio::R_reg<idr_descriptor>::get<gpio::C>(gpio::C pin_a) const
{
    return static_cast<gpio::R_reg<idr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & idr_descriptor::mask);
}

template<> template<> inline void gpio::WC_reg<odr_descriptor>::toggle<gpio::C>(gpio::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), odr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier));
}

template<> template<> inline void gpio::WC_reg<bsrr_descriptor>::toggle<gpio::C>(gpio::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), bsrr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * bsrr_descriptor::shift_multiplier));
}

template<> template<> inline gpio::WRC_reg<lckr_descriptor>::Flag gpio::WRC_reg<lckr_descriptor>::get<gpio::C>(gpio::C pin_a) const
{
    return static_cast<gpio::WRC_reg<lckr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & lckr_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<afr_descriptor>::toggle<gpio::C>(gpio::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<afr_descriptor>::Flag gpio::WRC_reg<afr_descriptor>::get<gpio::C>(gpio::C pin_a) const
{
    return static_cast<gpio::WRC_reg<afr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier) & afr_descriptor::mask);
}

template<> template<> inline void gpio::WC_reg<brr_descriptor>::toggle<gpio::C>(gpio::C pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}

constexpr gpio::Moder::Value operator<<(gpio::Moder::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::Moder::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio::Moder::Value operator<<(gpio::Moder::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::Moder::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}

constexpr gpio::Otyper::Value operator<<(gpio::Otyper::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::Otyper::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio::Otyper::Value operator<<(gpio::Otyper::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::Otyper::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}

constexpr gpio::Ospeedr::Value operator<<(gpio::Ospeedr::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::Ospeedr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio::Ospeedr::Value operator<<(gpio::Ospeedr::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::Ospeedr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}

constexpr gpio::Pupdr::Value operator<<(gpio::Pupdr::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::Pupdr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio::Pupdr::Value operator<<(gpio::Pupdr::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::Pupdr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}

constexpr gpio::Idr::Value operator<<(gpio::Idr::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::Idr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio::Idr::Value operator<<(gpio::Idr::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::Idr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}

constexpr gpio::Odr::Value operator<<(gpio::Odr::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::Odr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio::Odr::Value operator<<(gpio::Odr::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::Odr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Bsrr::Value operator<<(gpio::Bsrr::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::Bsrr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio::Bsrr::Value operator<<(gpio::Bsrr::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::Bsrr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Lckr::Value operator<<(gpio::Lckr::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::Lckr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Afr::Value operator<<(gpio::Afr::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::Afr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio::Afr::Value operator<<(gpio::Afr::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::Afr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}

constexpr gpio::Brr::Value operator<<(gpio::Brr::Flag flag_a, gpio::C pin_a)
{
    return static_cast<gpio::Brr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio::Brr::Value operator<<(gpio::Brr::Mask mask_a, gpio::C pin_a)
{
    return static_cast<gpio::Brr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
#endif
#if defined XMCU_GPIOD_PRESENT
template<> [[nodiscard]] constexpr gpio::Port* gpio::port<gpio::D>()
{
    return reinterpret_cast<gpio::Port*>(GPIOD_BASE);
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

template<> template<> inline void gpio::WRC_reg<moder_descriptor>::toggle<gpio::D>(gpio::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), moder_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<moder_descriptor>::Flag gpio::WRC_reg<moder_descriptor>::get<gpio::D>(gpio::D pin_a) const
{
    return static_cast<gpio::WRC_reg<moder_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier) & moder_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<otyper_descriptor>::toggle<gpio::D>(gpio::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            otyper_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<otyper_descriptor>::Flag gpio::WRC_reg<otyper_descriptor>::get<gpio::D>(gpio::D pin_a) const
{
    return static_cast<gpio::WRC_reg<otyper_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier) & otyper_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<ospeedr_descriptor>::toggle<gpio::D>(gpio::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            ospeedr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<ospeedr_descriptor>::Flag gpio::WRC_reg<ospeedr_descriptor>::get<gpio::D>(gpio::D pin_a) const
{
    return static_cast<gpio::WRC_reg<ospeedr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier) & ospeedr_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<pupdr_descriptor>::toggle<gpio::D>(gpio::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), pupdr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<pupdr_descriptor>::Flag gpio::WRC_reg<pupdr_descriptor>::get<gpio::D>(gpio::D pin_a) const
{
    return static_cast<gpio::WRC_reg<pupdr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & pupdr_descriptor::mask);
}

template<> template<> inline gpio::R_reg<idr_descriptor>::Flag gpio::R_reg<idr_descriptor>::get<gpio::D>(gpio::D pin_a) const
{
    return static_cast<gpio::R_reg<idr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & idr_descriptor::mask);
}

template<> template<> inline void gpio::WC_reg<odr_descriptor>::toggle<gpio::D>(gpio::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), odr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier));
}

template<> template<> inline void gpio::WC_reg<bsrr_descriptor>::toggle<gpio::D>(gpio::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), bsrr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * bsrr_descriptor::shift_multiplier));
}

template<> template<> inline gpio::WRC_reg<lckr_descriptor>::Flag gpio::WRC_reg<lckr_descriptor>::get<gpio::D>(gpio::D pin_a) const
{
    return static_cast<gpio::WRC_reg<lckr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & lckr_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<afr_descriptor>::toggle<gpio::D>(gpio::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<afr_descriptor>::Flag gpio::WRC_reg<afr_descriptor>::get<gpio::D>(gpio::D pin_a) const
{
    return static_cast<gpio::WRC_reg<afr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier) & afr_descriptor::mask);
}

template<> template<> inline void gpio::WC_reg<brr_descriptor>::toggle<gpio::D>(gpio::D pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}

constexpr gpio::Moder::Value operator<<(gpio::Moder::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::Moder::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio::Moder::Value operator<<(gpio::Moder::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::Moder::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}

constexpr gpio::Otyper::Value operator<<(gpio::Otyper::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::Otyper::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio::Otyper::Value operator<<(gpio::Otyper::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::Otyper::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}

constexpr gpio::Ospeedr::Value operator<<(gpio::Ospeedr::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::Ospeedr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio::Ospeedr::Value operator<<(gpio::Ospeedr::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::Ospeedr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}

constexpr gpio::Pupdr::Value operator<<(gpio::Pupdr::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::Pupdr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio::Pupdr::Value operator<<(gpio::Pupdr::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::Pupdr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}

constexpr gpio::Idr::Value operator<<(gpio::Idr::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::Idr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio::Idr::Value operator<<(gpio::Idr::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::Idr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}

constexpr gpio::Odr::Value operator<<(gpio::Odr::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::Odr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio::Odr::Value operator<<(gpio::Odr::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::Odr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Bsrr::Value operator<<(gpio::Bsrr::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::Bsrr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio::Bsrr::Value operator<<(gpio::Bsrr::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::Bsrr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Lckr::Value operator<<(gpio::Lckr::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::Lckr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Afr::Value operator<<(gpio::Afr::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::Afr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio::Afr::Value operator<<(gpio::Afr::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::Afr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}

constexpr gpio::Brr::Value operator<<(gpio::Brr::Flag flag_a, gpio::D pin_a)
{
    return static_cast<gpio::Brr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio::Brr::Value operator<<(gpio::Brr::Mask mask_a, gpio::D pin_a)
{
    return static_cast<gpio::Brr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
#endif
#if defined XMCU_GPIOF_PRESENT
template<> [[nodiscard]] constexpr gpio::Port* gpio::port<gpio::F>()
{
    return reinterpret_cast<gpio::Port*>(GPIOF_BASE);
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

template<> template<> inline void gpio::WRC_reg<moder_descriptor>::toggle<gpio::F>(gpio::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), moder_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<moder_descriptor>::Flag gpio::WRC_reg<moder_descriptor>::get<gpio::F>(gpio::F pin_a) const
{
    return static_cast<gpio::WRC_reg<moder_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier) & moder_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<otyper_descriptor>::toggle<gpio::F>(gpio::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            otyper_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<otyper_descriptor>::Flag gpio::WRC_reg<otyper_descriptor>::get<gpio::F>(gpio::F pin_a) const
{
    return static_cast<gpio::WRC_reg<otyper_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier) & otyper_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<ospeedr_descriptor>::toggle<gpio::F>(gpio::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v),
                            ospeedr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<ospeedr_descriptor>::Flag gpio::WRC_reg<ospeedr_descriptor>::get<gpio::F>(gpio::F pin_a) const
{
    return static_cast<gpio::WRC_reg<ospeedr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier) & ospeedr_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<pupdr_descriptor>::toggle<gpio::F>(gpio::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), pupdr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<pupdr_descriptor>::Flag gpio::WRC_reg<pupdr_descriptor>::get<gpio::F>(gpio::F pin_a) const
{
    return static_cast<gpio::WRC_reg<pupdr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & pupdr_descriptor::mask);
}

template<> template<> inline gpio::R_reg<idr_descriptor>::Flag gpio::R_reg<idr_descriptor>::get<gpio::F>(gpio::F pin_a) const
{
    return static_cast<gpio::R_reg<idr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & idr_descriptor::mask);
}

template<> template<> inline void gpio::WC_reg<odr_descriptor>::toggle<gpio::F>(gpio::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), odr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier));
}

template<> template<> inline void gpio::WC_reg<bsrr_descriptor>::toggle<gpio::F>(gpio::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), bsrr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * bsrr_descriptor::shift_multiplier));
}

template<> template<> inline gpio::WRC_reg<lckr_descriptor>::Flag gpio::WRC_reg<lckr_descriptor>::get<gpio::F>(gpio::F pin_a) const
{
    return static_cast<gpio::WRC_reg<lckr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier) & lckr_descriptor::mask);
}

template<> template<> inline void gpio::WRC_reg<afr_descriptor>::toggle<gpio::F>(gpio::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}
template<> template<> inline gpio::WRC_reg<afr_descriptor>::Flag gpio::WRC_reg<afr_descriptor>::get<gpio::F>(gpio::F pin_a) const
{
    return static_cast<gpio::WRC_reg<afr_descriptor>::Flag>(
        this->v >> (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier) & afr_descriptor::mask);
}

template<> template<> inline void gpio::WC_reg<brr_descriptor>::toggle<gpio::F>(gpio::F pin_a)
{
    xmcu::bit::flag::toggle(&(this->v), afr_descriptor::mask << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier));
}

constexpr gpio::Moder::Value operator<<(gpio::Moder::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::Moder::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}
constexpr gpio::Moder::Value operator<<(gpio::Moder::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::Moder::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * moder_descriptor::shift_multiplier)));
}

constexpr gpio::Otyper::Value operator<<(gpio::Otyper::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::Otyper::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}
constexpr gpio::Otyper::Value operator<<(gpio::Otyper::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::Otyper::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * otyper_descriptor::shift_multiplier)));
}

constexpr gpio::Ospeedr::Value operator<<(gpio::Ospeedr::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::Ospeedr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}
constexpr gpio::Ospeedr::Value operator<<(gpio::Ospeedr::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::Ospeedr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * ospeedr_descriptor::shift_multiplier)));
}

constexpr gpio::Pupdr::Value operator<<(gpio::Pupdr::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::Pupdr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}
constexpr gpio::Pupdr::Value operator<<(gpio::Pupdr::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::Pupdr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * pupdr_descriptor::shift_multiplier)));
}

constexpr gpio::Idr::Value operator<<(gpio::Idr::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::Idr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}
constexpr gpio::Idr::Value operator<<(gpio::Idr::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::Idr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * idr_descriptor::shift_multiplier)));
}

constexpr gpio::Odr::Value operator<<(gpio::Odr::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::Odr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio::Odr::Value operator<<(gpio::Odr::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::Odr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Bsrr::Value operator<<(gpio::Bsrr::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::Bsrr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}
constexpr gpio::Bsrr::Value operator<<(gpio::Bsrr::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::Bsrr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Lckr::Value operator<<(gpio::Lckr::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::Lckr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * odr_descriptor::shift_multiplier)));
}

constexpr gpio::Afr::Value operator<<(gpio::Afr::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::Afr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio::Afr::Value operator<<(gpio::Afr::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::Afr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}

constexpr gpio::Brr::Value operator<<(gpio::Brr::Flag flag_a, gpio::F pin_a)
{
    return static_cast<gpio::Brr::Value>(
        (static_cast<std::uint32_t>(flag_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
constexpr gpio::Brr::Value operator<<(gpio::Brr::Mask mask_a, gpio::F pin_a)
{
    return static_cast<gpio::Brr::Value>(
        (static_cast<std::uint32_t>(mask_a) << (static_cast<std::uint32_t>(pin_a) * afr_descriptor::shift_multiplier)));
}
#endif
} // namespace soc::st::arm::m0::u0::rm0503::peripherals::ll