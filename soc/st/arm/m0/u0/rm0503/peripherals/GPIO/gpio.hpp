#pragma once

/*
 *	Name: gpio.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cassert>

// CMSIS
#include <stm32u0xx.h>

// xmcu
#include <xmcu/Non_copyable.hpp>
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>
#include <xmcu/various.hpp>

// soc
#include <soc/st/arm/api.hpp>
#include <soc/st/arm/m0/u0/rm0503/peripherals/GPIO/base.hpp>

namespace soc::st::arm::m0::u0::rm0503::peripherals {
namespace ll {
struct gpio_clock : private xmcu::non_constructible
{
    template<typename Type> static void enable() = delete;
    template<typename Type> static void disable() = delete;

    template<typename Type> static bool is_enabled() = delete;
};

struct gpio : public gpio_base
{
#if defined XMCU_GPIOA_PRESENT
    using A = a;
#endif

#if defined XMCU_GPIOB_PRESENT
    using B = b;
#endif

#if defined XMCU_GPIOC_PRESENT
    using C = c;
#endif

#if defined XMCU_GPIOC_PRESENT
    using D = d;
#endif

    using clock = gpio_clock;

    struct Port : private xmcu::Non_copyable
    {
        volatile std::uint32_t moder;   /*!< GPIO port mode register,               Address offset: 0x00      */
        volatile std::uint32_t otyper;  /*!< GPIO port output type register,        Address offset: 0x04      */
        volatile std::uint32_t ospeedr; /*!< GPIO port output speed register,       Address offset: 0x08      */
        volatile std::uint32_t pupdr;   /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
        volatile std::uint32_t idr;     /*!< GPIO port input data register,         Address offset: 0x10      */
        volatile std::uint32_t odr;     /*!< GPIO port output data register,        Address offset: 0x14      */
        volatile std::uint32_t bsrr;    /*!< GPIO port bit set/reset  register,     Address offset: 0x18      */
        volatile std::uint32_t lckr;    /*!< GPIO port configuration lock register, Address offset: 0x1C      */
        volatile std::uint32_t afr[2];  /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
        volatile std::uint32_t brr;     /*!< GPIO Bit Reset register,               Address offset: 0x28      */
    };

    template<typename Port_t> static constexpr Port* interface();
};
} // namespace ll

#if !defined XMCU_LL_ONLY
struct gpio : public gpio_base
{
    enum class Mode : std::uint32_t
    {
        in,
        out,
        alternate,
        analog
    };
    enum class Type : std::uint32_t
    {
        push_pull = 0x0u,
        open_drain = 0x1u,
    };
    enum class Pull : std::uint32_t
    {
        none = 0x0u,
        up = 0x1u,
        down = 0x2u,
    };
    enum class Speed : std::uint32_t
    {
        low = 0x0u,
        medium = 0x1u,
        high = 0x2u,
        ultra = 0x3u,
    };
    enum class Level : std::uint32_t
    {
        low = 0x0u,
        high = 0x1u
    };

    using clock = ll::gpio_clock;

    template<Mode mode> struct Descriptor : private xmcu::non_constructible
    {
    };

    class Pad : private xmcu::Non_copyable
    {
    public:
        Level read() const
        {
            return static_cast<Level>(gpio::read(this->p_port, this->pin));
        }
        void write(Level level_a)
        {
            gpio::write(this->p_port, this->pin, static_cast<std::uint32_t>(level_a));
        }
        void toggle()
        {
            gpio::toggle(this->p_port, this->pin);
        }

    private:
        ll::gpio::Port* p_port = nullptr;
        std::uint32_t pin = std::numeric_limits<std::uint32_t>::max();

        friend gpio;
    };

    template<typename Pin_t> class Port
        : private ll::gpio::Port
        , private xmcu::non_constructible
    {
    public:
        using Pin = Pin_t;

        template<typename Descriptor_t> void enable(Pin_t pin_a, const Descriptor_t& descriptor_a) = delete;
        template<typename Descriptor_t> void enable(Pin_t pin_a, std::uint8_t function_a, const Descriptor_t& descriptor_a) = delete;
        template<typename Descriptor_t> void enable(Pin_t pin_a, const Descriptor_t& descriptor_a, Pad* p_out_pad_a) = delete;
        template<typename Descriptor_t>
        void enable(Pin_t pin_a, std::uint8_t function_a, const Descriptor_t& descriptor_a, Pad* p_out_pad_a) = delete;

        void disable(Pin_t pin_a) {}

        gpio::Level read(Pin_t pin_a) const
        {
            return static_cast<Level>(gpio::read(this, static_cast<std::uint32_t>(pin_a)));
        }
        void write(Pin_t pin_a, Level level_a)
        {
            gpio::write(this, static_cast<std::uint32_t>(pin_a), static_cast<std::uint32_t>(level_a));
        }
        void toggle(Pin_t pin_a)
        {
            gpio::toggle(this, static_cast<std::uint32_t>(pin_a));
        }

    private:
        friend gpio;
    };

#if defined XMCU_GPIOA_PRESENT
    using A = Port<a>;
#endif

#if defined XMCU_GPIOB_PRESENT
    using B = Port<b>;
#endif

#if defined XMCU_GPIOC_PRESENT
    using C = Port<c>;
#endif

#if defined XMCU_GPIOC_PRESENT
    using D = Port<d>;
#endif

    template<typename Port_t> constexpr static Port_t* interface() = delete;

private:
    static void enable_pin(ll::gpio::Port* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::in>& desc_a);
    static void enable_pin(ll::gpio::Port* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::out>& desc_a);
    static void enable_pin(ll::gpio::Port* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::analog>& desc_a);
    static void enable_pin(ll::gpio::Port* p_port_a,
                           std::uint32_t pin_a,
                           std::uint8_t function_a,
                           const gpio::Descriptor<gpio::Mode::alternate>& desc_a);

    static bool read(const ll::gpio::Port* p_port_a, std::uint32_t pin_a)
    {
        return xmcu::bit::is(p_port_a->idr, pin_a);
    }
    static void write(ll::gpio::Port* p_port_a, std::uint32_t pin_a, std::uint32_t level_a)
    {
        constexpr std::uint8_t mul[] = { 16u, 0u };
        p_port_a->bsrr = 0x1u << (static_cast<std::uint32_t>(pin_a) + mul[level_a]);
    }
    static void toggle(ll::gpio::Port* p_port_a, std::uint32_t pin_a)
    {
        xmcu::bit::toggle(&(p_port_a->odr), pin_a);
    }
};

template<> struct gpio::Descriptor<gpio::Mode::analog>
{
    gpio::Pull pull;
};
template<> struct gpio::Descriptor<gpio::Mode::in>
{
    gpio::Pull pull;
};
template<> struct gpio::Descriptor<gpio::Mode::out>
{
    gpio::Type type;
    gpio::Pull pull;
    gpio::Speed speed;
};
template<> struct gpio::Descriptor<gpio::Mode::alternate>
{
    gpio::Type type;
    gpio::Pull pull;
    gpio::Speed speed;
};

#if defined XMCU_GPIOA_PRESENT
template<> inline void ll::gpio_clock::enable<gpio::A>()
{
    xmcu::bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIOAEN);
}
template<> inline void ll::gpio_clock::disable<gpio::A>()
{
    xmcu::bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIOAEN);
}
template<> inline bool ll::gpio_clock::is_enabled<gpio::A>()
{
    return xmcu::bit::flag::is(RCC->IOPENR, RCC_IOPENR_GPIOAEN);
}

template<> template<>
inline void gpio::Port<gpio::A::Pin>::enable<gpio::Descriptor<gpio::Mode::analog>>(gpio::A::Pin pin_a,
                                                                                   const gpio::Descriptor<gpio::Mode::analog>& desc_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}
template<> template<>
inline void gpio::Port<gpio::A::Pin>::enable<gpio::Descriptor<gpio::Mode::analog>>(gpio::A::Pin pin_a,
                                                                                   const gpio::Descriptor<gpio::Mode::analog>& desc_a,
                                                                                   Pad* p_out_pad_a)
{
    assert(nullptr != p_out_pad_a);

    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);

    p_out_pad_a->pin = static_cast<std::uint32_t>(pin_a);
    p_out_pad_a->p_port = this;
}

template<> template<> inline void
gpio::Port<gpio::A::Pin>::enable<gpio::Descriptor<gpio::Mode::in>>(gpio::A::Pin pin_a, const gpio::Descriptor<gpio::Mode::in>& desc_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}
template<> template<>
inline void gpio::Port<gpio::A::Pin>::enable<gpio::Descriptor<gpio::Mode::in>>(gpio::A::Pin pin_a,
                                                                               const gpio::Descriptor<gpio::Mode::in>& desc_a,
                                                                               Pad* p_out_pad_a)
{
    assert(nullptr != p_out_pad_a);

    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);

    p_out_pad_a->pin = static_cast<std::uint32_t>(pin_a);
    p_out_pad_a->p_port = this;
}

template<> template<> inline void
gpio::Port<gpio::A::Pin>::enable<gpio::Descriptor<gpio::Mode::out>>(gpio::A::Pin pin_a, const gpio::Descriptor<gpio::Mode::out>& desc_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}
template<> template<>
inline void gpio::Port<gpio::A::Pin>::enable<gpio::Descriptor<gpio::Mode::out>>(gpio::A::Pin pin_a,
                                                                                const gpio::Descriptor<gpio::Mode::out>& desc_a,
                                                                                Pad* p_out_pad_a)
{
    assert(nullptr != p_out_pad_a);

    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);

    p_out_pad_a->pin = static_cast<std::uint32_t>(pin_a);
    p_out_pad_a->p_port = this;
}

template<> template<>
inline void gpio::Port<gpio::A::Pin>::enable<gpio::Descriptor<gpio::Mode::alternate>>(gpio::A::Pin pin_a,
                                                                                      std::uint8_t function_a,
                                                                                      const gpio::Descriptor<gpio::Mode::alternate>& desc_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), function_a, desc_a);
}
template<> template<>
inline void gpio::Port<gpio::A::Pin>::enable<gpio::Descriptor<gpio::Mode::alternate>>(gpio::A::Pin pin_a,
                                                                                      std::uint8_t function_a,
                                                                                      const gpio::Descriptor<gpio::Mode::alternate>& desc_a,
                                                                                      Pad* p_out_pad_a)
{
    assert(nullptr != p_out_pad_a);

    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), function_a, desc_a);

    p_out_pad_a->pin = static_cast<std::uint32_t>(pin_a);
    p_out_pad_a->p_port = this;
}
#endif

#if defined XMCU_GPIOB_PRESENT
template<> inline void ll::gpio_clock::enable<gpio::B>()
{
    xmcu::bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIOBEN);
}
template<> inline void ll::gpio_clock::disable<gpio::B>()
{
    xmcu::bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIOBEN);
}
template<> inline bool ll::gpio_clock::is_enabled<gpio::B>()
{
    return xmcu::bit::flag::is(RCC->IOPENR, RCC_IOPENR_GPIOBEN);
}

template<> template<>
inline void gpio::Port<gpio::B::Pin>::enable<gpio::Descriptor<gpio::Mode::analog>>(gpio::B::Pin pin_a,
                                                                                   const gpio::Descriptor<gpio::Mode::analog>& desc_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}
template<> template<>
inline void gpio::Port<gpio::B::Pin>::enable<gpio::Descriptor<gpio::Mode::analog>>(gpio::B::Pin pin_a,
                                                                                   const gpio::Descriptor<gpio::Mode::analog>& desc_a,
                                                                                   Pad* p_out_pad_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);

    p_out_pad_a->pin = static_cast<std::uint32_t>(pin_a);
    p_out_pad_a->p_port = this;
}

template<> template<> inline void
gpio::Port<gpio::B::Pin>::enable<gpio::Descriptor<gpio::Mode::in>>(gpio::B::Pin pin_a, const gpio::Descriptor<gpio::Mode::in>& desc_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}
template<> template<>
inline void gpio::Port<gpio::B::Pin>::enable<gpio::Descriptor<gpio::Mode::in>>(gpio::B::Pin pin_a,
                                                                               const gpio::Descriptor<gpio::Mode::in>& desc_a,
                                                                               Pad* p_out_pad_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);

    p_out_pad_a->pin = static_cast<std::uint32_t>(pin_a);
    p_out_pad_a->p_port = this;
}

template<> template<> inline void
gpio::Port<gpio::B::Pin>::enable<gpio::Descriptor<gpio::Mode::out>>(gpio::B::Pin pin_a, const gpio::Descriptor<gpio::Mode::out>& desc_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}
template<> template<>
inline void gpio::Port<gpio::B::Pin>::enable<gpio::Descriptor<gpio::Mode::out>>(gpio::B::Pin pin_a,
                                                                                const gpio::Descriptor<gpio::Mode::out>& desc_a,
                                                                                gpio::Pad* p_out_pad_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);

    p_out_pad_a->pin = static_cast<std::uint32_t>(pin_a);
    p_out_pad_a->p_port = this;
}

template<> template<>
inline void gpio::Port<gpio::B::Pin>::enable<gpio::Descriptor<gpio::Mode::alternate>>(gpio::B::Pin pin_a,
                                                                                      const gpio::Descriptor<gpio::Mode::alternate>& desc_a)
{
}
template<> template<>
inline void gpio::Port<gpio::B::Pin>::enable<gpio::Descriptor<gpio::Mode::alternate>>(gpio::B::Pin pin_a,
                                                                                      const gpio::Descriptor<gpio::Mode::alternate>& desc_a,
                                                                                      Pad* p_out_pad_a)
{
}
#endif

#if defined XMCU_GPIOC_PRESENT
template<> inline void ll::gpio_clock::enable<gpio::C>()
{
    xmcu::bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIOCEN);
}
template<> inline void ll::gpio_clock::disable<gpio::C>()
{
    xmcu::bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIOCEN);
}
template<> inline bool ll::gpio_clock::is_enabled<gpio::C>()
{
    return xmcu::bit::flag::is(RCC->IOPENR, RCC_IOPENR_GPIOCEN);
}

template<> template<>
inline void gpio::Port<gpio::C::Pin>::enable<gpio::Descriptor<gpio::Mode::analog>>(gpio::C::Pin pin_a,
                                                                                   const gpio::Descriptor<gpio::Mode::analog>& desc_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}
template<> template<>
inline void gpio::Port<gpio::C::Pin>::enable<gpio::Descriptor<gpio::Mode::analog>>(gpio::C::Pin pin_a,
                                                                                   const gpio::Descriptor<gpio::Mode::analog>& desc_a,
                                                                                   Pad* p_out_pad_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);

    p_out_pad_a->pin = static_cast<std::uint32_t>(pin_a);
    p_out_pad_a->p_port = this;
}

template<> template<> inline void
gpio::Port<gpio::C::Pin>::enable<gpio::Descriptor<gpio::Mode::in>>(gpio::C::Pin pin_a, const gpio::Descriptor<gpio::Mode::in>& desc_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}
template<> template<>
inline void gpio::Port<gpio::C::Pin>::enable<gpio::Descriptor<gpio::Mode::in>>(gpio::C::Pin pin_a,
                                                                               const gpio::Descriptor<gpio::Mode::in>& desc_a,
                                                                               Pad* p_out_pad_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);

    p_out_pad_a->pin = static_cast<std::uint32_t>(pin_a);
    p_out_pad_a->p_port = this;
}

template<> template<> inline void
gpio::Port<gpio::C::Pin>::enable<gpio::Descriptor<gpio::Mode::out>>(gpio::C::Pin pin_a, const gpio::Descriptor<gpio::Mode::out>& desc_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}
template<> template<>
inline void gpio::Port<gpio::C::Pin>::enable<gpio::Descriptor<gpio::Mode::out>>(gpio::C::Pin pin_a,
                                                                                const gpio::Descriptor<gpio::Mode::out>& desc_a,
                                                                                Pad* p_out_pad_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);

    p_out_pad_a->pin = static_cast<std::uint32_t>(pin_a);
    p_out_pad_a->p_port = this;
}

template<> template<>
inline void gpio::Port<gpio::C::Pin>::enable<gpio::Descriptor<gpio::Mode::alternate>>(gpio::C::Pin pin_a,
                                                                                      const gpio::Descriptor<gpio::Mode::alternate>& desc_a)
{
}
template<> template<>
inline void gpio::Port<gpio::C::Pin>::enable<gpio::Descriptor<gpio::Mode::alternate>>(gpio::C::Pin pin_a,
                                                                                      const gpio::Descriptor<gpio::Mode::alternate>& desc_a,
                                                                                      Pad* p_out_pad_a)
{
}
#endif

#if defined XMCU_GPIOD_PRESENT
template<> inline void ll::gpio_clock::enable<gpio::D>()
{
    xmcu::bit::flag::set(&(RCC->IOPENR), RCC_IOPENR_GPIODEN);
}
template<> inline void ll::gpio_clock::disable<gpio::D>()
{
    xmcu::bit::flag::clear(&(RCC->IOPENR), RCC_IOPENR_GPIODEN);
}
template<> inline bool ll::gpio_clock::is_enabled<gpio::D>()
{
    return xmcu::bit::flag::is(RCC->IOPENR, RCC_IOPENR_GPIODEN);
}

template<> template<>
inline void gpio::Port<gpio::D::Pin>::enable<gpio::Descriptor<gpio::Mode::analog>>(gpio::D::Pin pin_a,
                                                                                   const gpio::Descriptor<gpio::Mode::analog>& desc_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}
template<> template<>
inline void gpio::Port<gpio::D::Pin>::enable<gpio::Descriptor<gpio::Mode::analog>>(gpio::D::Pin pin_a,
                                                                                   const gpio::Descriptor<gpio::Mode::analog>& desc_a,
                                                                                   Pad* p_out_pad_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);

    p_out_pad_a->pin = static_cast<std::uint32_t>(pin_a);
    p_out_pad_a->p_port = this;
}

template<> template<> inline void
gpio::Port<gpio::D::Pin>::enable<gpio::Descriptor<gpio::Mode::in>>(gpio::D::Pin pin_a, const gpio::Descriptor<gpio::Mode::in>& desc_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}
template<> template<>
inline void gpio::Port<gpio::D::Pin>::enable<gpio::Descriptor<gpio::Mode::in>>(gpio::D::Pin pin_a,
                                                                               const gpio::Descriptor<gpio::Mode::in>& desc_a,
                                                                               Pad* p_out_pad_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);

    p_out_pad_a->pin = static_cast<std::uint32_t>(pin_a);
    p_out_pad_a->p_port = this;
}

template<> template<> inline void
gpio::Port<gpio::D::Pin>::enable<gpio::Descriptor<gpio::Mode::out>>(gpio::D::Pin pin_a, const gpio::Descriptor<gpio::Mode::out>& desc_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}
template<> template<>
inline void gpio::Port<gpio::D::Pin>::enable<gpio::Descriptor<gpio::Mode::out>>(gpio::D::Pin pin_a,
                                                                                const gpio::Descriptor<gpio::Mode::out>& desc_a,
                                                                                Pad* p_out_pad_a)
{
    gpio::enable_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);

    p_out_pad_a->pin = static_cast<std::uint32_t>(pin_a);
    p_out_pad_a->p_port = this;
}

template<> template<>
inline void gpio::Port<gpio::D::Pin>::enable<gpio::Descriptor<gpio::Mode::alternate>>(gpio::D::Pin pin_a,
                                                                                      const gpio::Descriptor<gpio::Mode::alternate>& desc_a)
{
}
template<> template<>
inline void gpio::Port<gpio::D::Pin>::enable<gpio::Descriptor<gpio::Mode::alternate>>(gpio::D::Pin pin_a,
                                                                                      const gpio::Descriptor<gpio::Mode::alternate>& desc_a,
                                                                                      Pad* p_out_pad_a)
{
}
#endif
#endif

#if !defined XMCU_LL_ONLY
#if defined XMCU_GPIOA_PRESENT
template<> inline constexpr gpio::A* gpio::interface<gpio::A>()
{
    return reinterpret_cast<gpio::A*>(GPIOA_BASE);
}
#endif
#if defined XMCU_GPIOB_PRESENT
template<> inline constexpr gpio::B* gpio::interface<gpio::B>()
{
    return reinterpret_cast<gpio::B*>(GPIOB_BASE);
}
#endif
#if defined XMCU_GPIOC_PRESENT
template<> inline constexpr gpio::C* gpio::interface<gpio::C>()
{
    return reinterpret_cast<gpio::C*>(GPIOC_BASE);
}
#if defined XMCU_GPIOD_PRESENT
template<> inline constexpr gpio::D* gpio::interface<gpio::D>()
{
    return reinterpret_cast<gpio::D*>(GPIOD_BASE);
}
#endif
#endif
#endif
#if defined XMCU_GPIOA_PRESENT
template<> inline constexpr ll::gpio::Port* ll::gpio::interface<ll::gpio::A>()
{
    return reinterpret_cast<ll::gpio::Port*>(GPIOA_BASE);
}
#endif
#if defined XMCU_GPIOB_PRESENT
template<> inline constexpr ll::gpio::Port* ll::gpio::interface<ll::gpio::B>()
{
    return reinterpret_cast<ll::gpio::Port*>(GPIOB_BASE);
}
#endif
#if defined XMCU_GPIOC_PRESENT
template<> inline constexpr ll::gpio::Port* ll::gpio::interface<ll::gpio::C>()
{
    return reinterpret_cast<ll::gpio::Port*>(GPIOC_BASE);
}
#endif
#if defined XMCU_GPIOC_PRESENT
template<> inline constexpr ll::gpio::Port* ll::gpio::interface<ll::gpio::D>()
{
    return reinterpret_cast<ll::gpio::Port*>(GPIOD_BASE);
}
#endif

} // namespace soc::st::arm::m0::u0::rm0503::peripherals