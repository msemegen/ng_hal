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
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>
#include <xmcu/non_copyable.hpp>
#include <xmcu/various.hpp>

// soc
#include <soc/st/arm/IRQ_priority.hpp>
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
    using A = gpio_base::A;
#endif

#if defined XMCU_GPIOB_PRESENT
    using B = gpio_base::B;
#endif

#if defined XMCU_GPIOC_PRESENT
    using C = gpio_base::C;
#endif

#if defined XMCU_GPIOD_PRESENT
    using D = gpio_base::D;
#endif

#if defined XMCU_GPIOF_PRESENT
    using F = gpio_base::F;
#endif

    using clock = gpio_clock;

    struct Port : private xmcu::non_copyable
    {
        volatile std::uint32_t moder;   // port mode register
        volatile std::uint32_t otyper;  // port output type register
        volatile std::uint32_t ospeedr; // port output speed register
        volatile std::uint32_t pupdr;   // port pull-up/pull-down register
        volatile std::uint32_t idr;     // port input data register
        volatile std::uint32_t odr;     // port output data register
        volatile std::uint32_t bsrr;    // port bit set/reset  register
        volatile std::uint32_t lckr;    // port configuration lock register
        volatile std::uint32_t afr[2];  // alternate function registers
        volatile std::uint32_t brr;     // bit reset register
    };

    template<typename Port_t> [[nodiscard]] static constexpr Port* port() = delete;
};

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
#endif
} // namespace ll

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
    enum class Edge : std::uint32_t
    {
        rising = 0x1u,
        falling = 0x2u
    };

    using clock = ll::gpio_clock;

    template<Mode mode> struct Descriptor : private xmcu::non_constructible
    {
    };

    template<typename Port_a, api::traits traits_t> class Port : xmcu::non_constructible
    {
    };

    class Pad : private xmcu::non_copyable
    {
    public:
        constexpr Pad()
            : p_port(nullptr)
            , pin(0u)
        {
        }

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
        Pad(ll::gpio::Port* p_port_a, std::uint32_t pin_a)
            : p_port(p_port_a)
            , pin(pin_a)
        {
        }

        ll::gpio::Port* p_port = nullptr;
        std::uint32_t pin = std::numeric_limits<std::uint32_t>::max();

        friend gpio;
    };

    struct async : private xmcu::non_constructible
    {
        static void enable(const IRQ_priority& priority_a);
        static void disable();

        struct handler : private xmcu::non_constructible
        {
            static void on_rise(std::uint32_t pin_a);
            static void on_fall(std::uint32_t pin_a);
        };
    };

    template<typename Port_t, api::traits traits_t> [[nodiscard]] constexpr static Port<Port_t, traits_t>* port() = delete;

private:
    static void configure_pin(ll::gpio::Port* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::in>& desc_a);
    static void configure_pin(ll::gpio::Port* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::out>& desc_a);
    static void configure_pin(ll::gpio::Port* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::analog>& desc_a);
    static void configure_pin(ll::gpio::Port* p_port_a,
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

    static bool is_irq_slot_enabled(std::uint32_t port_a, std::uint32_t pin_a);
    static void enable_irq_slot(std::uint32_t port_a, std::uint32_t pin_a, volatile std::uint32_t* p_array_a, std::size_t array_length_a);
    static void disable_irq_slot(std::uint32_t port_a, std::uint32_t pin_a, volatile std::uint32_t* p_array_a, std::size_t array_length_a);
    static void set_irq_edge(std::uint32_t port_a, Edge edge_a);

    static inline std::uint32_t enabled_slots[4] = { 0x0u, 0x0u, 0x0u, 0x0u };
};

constexpr gpio::Edge operator|(gpio::Edge left_a, gpio::Edge right_a)
{
    return static_cast<gpio::Edge>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr gpio::Edge operator&(gpio::Edge left_a, gpio::Edge right_a)
{
    return static_cast<gpio::Edge>(static_cast<std::uint32_t>(left_a) & static_cast<std::uint32_t>(right_a));
}

template<typename Port_t> class gpio::Port<Port_t, api::traits::sync> : private ll::gpio::Port
{
public:
    using Pin = Port_t;

    template<typename Descriptor_t> void set_pin_descriptor(Pin pin_a, const Descriptor_t& desc_a) = delete;
    template<typename Descriptor_t> void set_pin_descriptor(Pin pin_a, std::uint8_t function_a, const Descriptor_t& desc_a) = delete;

    [[nodiscard]] gpio::Level read(Pin pin_a) const
    {
        return static_cast<Level>(gpio::read(this, static_cast<std::uint32_t>(pin_a)));
    }
    void write(Pin pin_a, Level level_a)
    {
        gpio::write(this, static_cast<std::uint32_t>(pin_a), static_cast<std::uint32_t>(level_a));
    }
    void toggle(Pin pin_a)
    {
        gpio::toggle(this, static_cast<std::uint32_t>(pin_a));
    }

    template<typename Type_t> [[nodiscard]] constexpr Type_t view(Pin pin_a) = delete;

private:
    friend gpio;
};
template<typename Port_t> class gpio::Port<Port_t, api::traits::async> : private ll::gpio::Port
{
public:
    using Pin = Port_t;

    void set_pin_descriptor(Pin pin_a, const gpio::Descriptor<gpio::Mode::in>& descriptor_a)
    {
        gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), descriptor_a);
    }

    [[nodiscard]] bool is_taken(Pin pin_a) const;

    void start(Pin pin_a, Edge edge_a);
    void stop(Pin pin_a);

private:
    friend gpio;
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
template<> [[nodiscard]] constexpr gpio::Port<gpio::A, api::traits::sync>* gpio::port<gpio::A, api::traits::sync>()
{
    return reinterpret_cast<gpio::Port<gpio::A, api::traits::sync>*>(GPIOA_BASE);
}
template<> [[nodiscard]] constexpr gpio::Port<gpio::A, api::traits::async>* gpio::port<gpio::A, api::traits::async>()
{
    return reinterpret_cast<gpio::Port<gpio::A, api::traits::async>*>(GPIOA_BASE);
}

template<> template<> [[nodiscard]] constexpr gpio::Pad gpio::Port<gpio::A, api::traits::sync>::view<gpio::Pad>(gpio::A pin_a)
{
    return { ll::gpio::port<ll::gpio::A>(), static_cast<std::uint32_t>(pin_a) };
}

template<> template<> inline void gpio::Port<gpio::A, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::analog>>(
    gpio::A pin_a,
    const gpio::Descriptor<gpio::Mode::analog>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void
gpio::Port<gpio::A, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::in>>(gpio::A pin_a,
                                                                                             const gpio::Descriptor<gpio::Mode::in>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void gpio::Port<gpio::A, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::out>>(
    gpio::A pin_a,
    const gpio::Descriptor<gpio::Mode::out>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void gpio::Port<gpio::A, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::alternate>>(
    gpio::A pin_a,
    std::uint8_t function_a,
    const gpio::Descriptor<gpio::Mode::alternate>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), function_a, desc_a);
}

template<> [[nodiscard]] inline bool gpio::Port<gpio::A, api::traits::async>::is_taken(Pin pin_a) const
{
    return gpio::is_irq_slot_enabled(0u, static_cast<std::uint32_t>(pin_a));
}
template<> inline void gpio::Port<gpio::A, api::traits::async>::start(Pin pin_a, gpio::Edge edge_a)
{
    assert(false == gpio::is_irq_slot_enabled(1u, static_cast<std::uint32_t>(pin_a)));

    gpio::enable_irq_slot(1u, static_cast<std::uint32_t>(pin_a), gpio::enabled_slots, xmcu::various::countof(gpio::enabled_slots));
    gpio::enable_irq_slot(0u, static_cast<std::uint32_t>(pin_a), EXTI->EXTICR, xmcu::various::countof(EXTI->EXTICR));
    gpio::set_irq_edge(static_cast<std::uint32_t>(pin_a), edge_a);
    xmcu::bit::set(&(EXTI->IMR1), static_cast<std::uint32_t>(pin_a));
}
template<> inline void gpio::Port<gpio::A, api::traits::async>::stop(Pin pin_a)
{
    gpio::disable_irq_slot(1u, static_cast<std::uint32_t>(pin_a), gpio::enabled_slots, xmcu::various::countof(gpio::enabled_slots));
    gpio::disable_irq_slot(0u, static_cast<std::uint32_t>(pin_a), EXTI->EXTICR, xmcu::various::countof(EXTI->EXTICR));
    xmcu::bit::clear(&(EXTI->IMR1), static_cast<std::uint32_t>(pin_a));
}
#endif
#if defined XMCU_GPIOB_PRESENT
template<> [[nodiscard]] constexpr gpio::Port<gpio::B, api::traits::sync>* gpio::port<gpio::B, api::traits::sync>()
{
    return reinterpret_cast<gpio::Port<gpio::B, api::traits::sync>*>(GPIOB_BASE);
}
template<> [[nodiscard]] constexpr gpio::Port<gpio::B, api::traits::async>* gpio::port<gpio::B, api::traits::async>()
{
    return reinterpret_cast<gpio::Port<gpio::B, api::traits::async>*>(GPIOB_BASE);
}

template<> template<> [[nodiscard]] constexpr gpio::Pad gpio::Port<gpio::B, api::traits::sync>::view<gpio::Pad>(gpio::B pin_a)
{
    return { ll::gpio::port<ll::gpio::B>(), static_cast<std::uint32_t>(pin_a) };
}

template<> template<> inline void gpio::Port<gpio::B, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::analog>>(
    gpio::B pin_a,
    const gpio::Descriptor<gpio::Mode::analog>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void
gpio::Port<gpio::B, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::in>>(gpio::B pin_a,
                                                                                             const gpio::Descriptor<gpio::Mode::in>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void gpio::Port<gpio::B, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::out>>(
    gpio::B pin_a,
    const gpio::Descriptor<gpio::Mode::out>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void gpio::Port<gpio::B, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::alternate>>(
    gpio::B pin_a,
    std::uint8_t function_a,
    const gpio::Descriptor<gpio::Mode::alternate>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), function_a, desc_a);
}

template<> [[nodiscard]] inline bool gpio::Port<gpio::B, api::traits::async>::is_taken(Pin pin_a) const
{
    return gpio::is_irq_slot_enabled(2u, static_cast<std::uint32_t>(pin_a));
}
template<> inline void gpio::Port<gpio::B, api::traits::async>::start(Pin pin_a, gpio::Edge edge_a)
{
    assert(false == gpio::is_irq_slot_enabled(2u, static_cast<std::uint32_t>(pin_a)));

    gpio::enable_irq_slot(2u, static_cast<std::uint32_t>(pin_a), gpio::enabled_slots, xmcu::various::countof(gpio::enabled_slots));
    gpio::enable_irq_slot(1u, static_cast<std::uint32_t>(pin_a), EXTI->EXTICR, xmcu::various::countof(EXTI->EXTICR));
    gpio::set_irq_edge(static_cast<std::uint32_t>(pin_a), edge_a);
    xmcu::bit::set(&(EXTI->IMR1), static_cast<std::uint32_t>(pin_a));
}
template<> inline void gpio::Port<gpio::B, api::traits::async>::stop(Pin pin_a)
{
    gpio::disable_irq_slot(2u, static_cast<std::uint32_t>(pin_a), gpio::enabled_slots, xmcu::various::countof(gpio::enabled_slots));
    gpio::disable_irq_slot(1u, static_cast<std::uint32_t>(pin_a), EXTI->EXTICR, xmcu::various::countof(EXTI->EXTICR));
    xmcu::bit::clear(&(EXTI->IMR1), static_cast<std::uint32_t>(pin_a));
}
#endif
#if defined XMCU_GPIOC_PRESENT
template<> [[nodiscard]] constexpr gpio::Port<gpio::C, api::traits::sync>* gpio::port<gpio::C, api::traits::sync>()
{
    return reinterpret_cast<gpio::Port<gpio::C, api::traits::sync>*>(GPIOC_BASE);
}
template<> [[nodiscard]] constexpr gpio::Port<gpio::C, api::traits::async>* gpio::port<gpio::C, api::traits::async>()
{
    return reinterpret_cast<gpio::Port<gpio::C, api::traits::async>*>(GPIOC_BASE);
}

template<> template<> [[nodiscard]] constexpr gpio::Pad gpio::Port<gpio::C, api::traits::sync>::view<gpio::Pad>(gpio::C pin_a)
{
    return { ll::gpio::port<ll::gpio::C>(), static_cast<std::uint32_t>(pin_a) };
}

template<> template<> inline void gpio::Port<gpio::C, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::analog>>(
    gpio::C pin_a,
    const gpio::Descriptor<gpio::Mode::analog>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void
gpio::Port<gpio::C, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::in>>(gpio::C pin_a,
                                                                                             const gpio::Descriptor<gpio::Mode::in>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void gpio::Port<gpio::C, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::out>>(
    gpio::C pin_a,
    const gpio::Descriptor<gpio::Mode::out>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void gpio::Port<gpio::C, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::alternate>>(
    gpio::C pin_a,
    std::uint8_t function_a,
    const gpio::Descriptor<gpio::Mode::alternate>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), function_a, desc_a);
}

template<> [[nodiscard]] inline bool gpio::Port<gpio::C, api::traits::async>::is_taken(Pin pin_a) const
{
    return gpio::is_irq_slot_enabled(3u, static_cast<std::uint32_t>(pin_a));
}
template<> inline void gpio::Port<gpio::C, api::traits::async>::start(Pin pin_a, gpio::Edge edge_a)
{
    assert(false == gpio::is_irq_slot_enabled(3u, static_cast<std::uint32_t>(pin_a)));

    gpio::enable_irq_slot(3u, static_cast<std::uint32_t>(pin_a), gpio::enabled_slots, xmcu::various::countof(gpio::enabled_slots));
    gpio::enable_irq_slot(2u, static_cast<std::uint32_t>(pin_a), EXTI->EXTICR, xmcu::various::countof(EXTI->EXTICR));
    gpio::set_irq_edge(static_cast<std::uint32_t>(pin_a), edge_a);
    xmcu::bit::set(&(EXTI->IMR1), static_cast<std::uint32_t>(pin_a));
}
template<> inline void gpio::Port<gpio::C, api::traits::async>::stop(Pin pin_a)
{
    gpio::disable_irq_slot(3u, static_cast<std::uint32_t>(pin_a), gpio::enabled_slots, xmcu::various::countof(gpio::enabled_slots));
    gpio::disable_irq_slot(2u, static_cast<std::uint32_t>(pin_a), EXTI->EXTICR, xmcu::various::countof(EXTI->EXTICR));
    xmcu::bit::clear(&(EXTI->IMR1), static_cast<std::uint32_t>(pin_a));
}
#endif
#if defined XMCU_GPIOD_PRESENT
template<> [[nodiscard]] constexpr gpio::Port<gpio::D, api::traits::sync>* gpio::port<gpio::D, api::traits::sync>()
{
    return reinterpret_cast<gpio::Port<gpio::D, api::traits::sync>*>(GPIOD_BASE);
}
template<> [[nodiscard]] constexpr gpio::Port<gpio::D, api::traits::async>* gpio::port<gpio::D, api::traits::async>()
{
    return reinterpret_cast<gpio::Port<gpio::D, api::traits::async>*>(GPIOD_BASE);
}

template<> template<> [[nodiscard]] constexpr gpio::Pad gpio::Port<gpio::D, api::traits::sync>::view<gpio::Pad>(gpio::D pin_a)
{
    return { ll::gpio::port<ll::gpio::D>(), static_cast<std::uint32_t>(pin_a) };
}

template<> template<> inline void gpio::Port<gpio::D, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::analog>>(
    gpio::D pin_a,
    const gpio::Descriptor<gpio::Mode::analog>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void
gpio::Port<gpio::D, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::in>>(gpio::D pin_a,
                                                                                             const gpio::Descriptor<gpio::Mode::in>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void gpio::Port<gpio::D, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::out>>(
    gpio::D pin_a,
    const gpio::Descriptor<gpio::Mode::out>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void gpio::Port<gpio::D, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::alternate>>(
    gpio::D pin_a,
    std::uint8_t function_a,
    const gpio::Descriptor<gpio::Mode::alternate>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), function_a, desc_a);
}

template<> [[nodiscard]] inline bool gpio::Port<gpio::D, api::traits::async>::is_taken(Pin pin_a) const
{
    return gpio::is_irq_slot_enabled(4u, static_cast<std::uint32_t>(pin_a));
}
template<> inline void gpio::Port<gpio::D, api::traits::async>::start(Pin pin_a, gpio::Edge edge_a)
{
    assert(false == gpio::is_irq_slot_enabled(4u, static_cast<std::uint32_t>(pin_a)));

    gpio::enable_irq_slot(4u, static_cast<std::uint32_t>(pin_a), gpio::enabled_slots, xmcu::various::countof(gpio::enabled_slots));
    gpio::enable_irq_slot(3u, static_cast<std::uint32_t>(pin_a), EXTI->EXTICR, xmcu::various::countof(EXTI->EXTICR));
    gpio::set_irq_edge(static_cast<std::uint32_t>(pin_a), edge_a);
    xmcu::bit::set(&(EXTI->IMR1), static_cast<std::uint32_t>(pin_a));
}
template<> inline void gpio::Port<gpio::D, api::traits::async>::stop(Pin pin_a)
{
    gpio::disable_irq_slot(4u, static_cast<std::uint32_t>(pin_a), gpio::enabled_slots, xmcu::various::countof(gpio::enabled_slots));
    gpio::disable_irq_slot(3u, static_cast<std::uint32_t>(pin_a), EXTI->EXTICR, xmcu::various::countof(EXTI->EXTICR));
    xmcu::bit::clear(&(EXTI->IMR1), static_cast<std::uint32_t>(pin_a));
}
#endif
#if defined XMCU_GPIOF_PRESENT
template<> [[nodiscard]] constexpr gpio::Port<gpio::F, api::traits::sync>* gpio::port<gpio::F, api::traits::sync>()
{
    return reinterpret_cast<gpio::Port<gpio::F, api::traits::sync>*>(GPIOF_BASE);
}
template<> [[nodiscard]] constexpr gpio::Port<gpio::F, api::traits::async>* gpio::port<gpio::F, api::traits::async>()
{
    return reinterpret_cast<gpio::Port<gpio::F, api::traits::async>*>(GPIOF_BASE);
}

template<> template<> [[nodiscard]] constexpr gpio::Pad gpio::Port<gpio::F, api::traits::sync>::view<gpio::Pad>(gpio::F pin_a)
{
    return { ll::gpio::port<ll::gpio::F>(), static_cast<std::uint32_t>(pin_a) };
}

template<> template<> inline void gpio::Port<gpio::F, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::analog>>(
    gpio::F pin_a,
    const gpio::Descriptor<gpio::Mode::analog>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void
gpio::Port<gpio::F, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::in>>(gpio::F pin_a,
                                                                                             const gpio::Descriptor<gpio::Mode::in>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void gpio::Port<gpio::F, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::out>>(
    gpio::F pin_a,
    const gpio::Descriptor<gpio::Mode::out>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), desc_a);
}

template<> template<> inline void gpio::Port<gpio::F, api::traits::sync>::set_pin_descriptor<gpio::Descriptor<gpio::Mode::alternate>>(
    gpio::F pin_a,
    std::uint8_t function_a,
    const gpio::Descriptor<gpio::Mode::alternate>& desc_a)
{
    gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), function_a, desc_a);
}

template<> [[nodiscard]] inline bool gpio::Port<gpio::F, api::traits::async>::is_taken(Pin pin_a) const
{
    return gpio::is_irq_slot_enabled(6u, static_cast<std::uint32_t>(pin_a));
}
template<> inline void gpio::Port<gpio::F, api::traits::async>::start(Pin pin_a, gpio::Edge edge_a)
{
    assert(false == gpio::is_irq_slot_enabled(6u, static_cast<std::uint32_t>(pin_a)));

    gpio::enable_irq_slot(6u, static_cast<std::uint32_t>(pin_a), gpio::enabled_slots, xmcu::various::countof(gpio::enabled_slots));
    gpio::enable_irq_slot(5u, static_cast<std::uint32_t>(pin_a), EXTI->EXTICR, xmcu::various::countof(EXTI->EXTICR));
    gpio::set_irq_edge(static_cast<std::uint32_t>(pin_a), edge_a);
    xmcu::bit::set(&(EXTI->IMR1), static_cast<std::uint32_t>(pin_a));
}
template<> inline void gpio::Port<gpio::F, api::traits::async>::stop(Pin pin_a)
{
    gpio::disable_irq_slot(6u, static_cast<std::uint32_t>(pin_a), gpio::enabled_slots, xmcu::various::countof(gpio::enabled_slots));
    gpio::disable_irq_slot(5u, static_cast<std::uint32_t>(pin_a), EXTI->EXTICR, xmcu::various::countof(EXTI->EXTICR));
    xmcu::bit::clear(&(EXTI->IMR1), static_cast<std::uint32_t>(pin_a));
}
#endif
} // namespace soc::st::arm::m0::u0::rm0503::peripherals