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
#include <xmcu/Limited.hpp>
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>
#include <xmcu/non_copyable.hpp>
#include <xmcu/various.hpp>

// soc
#include <soc/st/arm/IRQ_priority.hpp>
#include <soc/st/arm/api.hpp>
#include <soc/st/arm/m0/u0/rm0503/peripherals/GPIO/base.hpp>
#include <soc/st/arm/m0/u0/rm0503/peripherals/GPIO/gpio_ll.hpp>

namespace soc::st::arm::m0::u0::rm0503::peripherals {
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
        push_pull = static_cast<std::uint32_t>(ll::gpio::OTYPER::push_pull),
        open_drain = static_cast<std::uint32_t>(ll::gpio::OTYPER::open_drain),
    };
    enum class Pull : std::uint32_t
    {
        none = static_cast<std::uint32_t>(ll::gpio::PUPDR::none),
        up = static_cast<std::uint32_t>(ll::gpio::PUPDR::pull_up),
        down = static_cast<std::uint32_t>(ll::gpio::PUPDR::pull_down),
    };
    enum class Speed : std::uint32_t
    {
        low = static_cast<std::uint32_t>(ll::gpio::OSPEEDR::low),
        medium = static_cast<std::uint32_t>(ll::gpio::OSPEEDR::medium),
        high = static_cast<std::uint32_t>(ll::gpio::OSPEEDR::high),
        ultra = static_cast<std::uint32_t>(ll::gpio::OSPEEDR::ultra),
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
            : p_registers(nullptr)
            , pin(0u)
        {
        }

        [[nodiscard]] Level read() const
        {
            return static_cast<Level>(gpio::read(this->p_registers, this->pin));
        }
        void write(Level level_a)
        {
            gpio::write(this->p_registers, this->pin, static_cast<ll::gpio::ODR::Flag>(level_a));
        }
        void toggle()
        {
            gpio::toggle(this->p_registers, this->pin);
        }

    private:
        Pad(ll::gpio::Registers* p_registers_a, std::uint32_t pin_a)
            : p_registers(p_registers_a)
            , pin(pin_a)
        {
        }

        ll::gpio::Registers* p_registers = nullptr;
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
    static void configure_pin(ll::gpio::Registers* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::in>& desc_a);
    static void configure_pin(ll::gpio::Registers* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::out>& desc_a);
    static void configure_pin(ll::gpio::Registers* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::analog>& desc_a);
    static void configure_pin(ll::gpio::Registers* p_port_a,
                              std::uint32_t pin_a,
                              std::uint32_t function_a,
                              const gpio::Descriptor<gpio::Mode::alternate>& desc_a);

    static ll::gpio::IDR::Flag read(const ll::gpio::Registers* p_port_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a)
    {
        return static_cast<ll::gpio::IDR::Flag>(xmcu::bit::is(p_port_a->idr, pin_a));
    }
    static void write(ll::gpio::Registers* p_port_a, std::uint32_t pin_a, ll::gpio::ODR::Flag level_a)
    {
        xmcu::bit::flag::set(&(p_port_a->odr), static_cast<ll::gpio::ODR::Flag>(level_a) << pin_a);
    }
    static void toggle(ll::gpio::Registers* p_port_a, std::uint32_t pin_a)
    {
        xmcu::bit::toggle(&(p_port_a->odr), xmcu::Limited<std::uint32_t, 0u, 15u>(pin_a));
    }

    static bool is_irq_slot_enabled(std::uint32_t port_a, xmcu::Limited<std::uint32_t, 0u, 15u> pin_a);
    static void enable_irq_slot(std::uint32_t port_a, std::uint32_t pin_a, volatile std::uint32_t* p_array_a, std::size_t array_length_a);
    static void disable_irq_slot(std::uint32_t port_a, std::uint32_t pin_a, volatile std::uint32_t* p_array_a, std::size_t array_length_a);
    static void set_irq_edge(xmcu::Limited<std::uint32_t, 0u, 15u> pin_a, Edge edge_a);

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

template<typename Port_t> class gpio::Port<Port_t, api::traits::sync> : private ll::gpio::Registers
{
public:
    using Pin = Port_t;

    template<typename Descriptor_t> void set_pin_descriptor(Pin pin_a, const Descriptor_t& desc_a) = delete;
    template<typename Descriptor_t> void set_pin_descriptor(Pin pin_a, std::uint32_t function_a, const Descriptor_t& desc_a) = delete;

    [[nodiscard]] gpio::Level read(Pin pin_a) const
    {
        return static_cast<Level>(gpio::read(this, static_cast<std::uint32_t>(pin_a)));
    }
    void write(Pin pin_a, Level level_a)
    {
        gpio::write(this, static_cast<std::uint32_t>(pin_a), static_cast<ll::gpio::ODR::Flag>(level_a));
    }
    void toggle(Pin pin_a)
    {
        gpio::toggle(this, static_cast<std::uint32_t>(pin_a));
    }

    template<typename Type_t> [[nodiscard]] constexpr Type_t view(Pin pin_a) = delete;

private:
    friend gpio;
};
template<typename Port_t> class gpio::Port<Port_t, api::traits::async> : private ll::gpio::Registers
{
public:
    using Pin = Port_t;

    void set_pin_descriptor(Pin pin_a, const gpio::Descriptor<gpio::Mode::analog>& descriptor_a)
    {
        gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), descriptor_a);
    }
    void set_pin_descriptor(Pin pin_a, const gpio::Descriptor<gpio::Mode::in>& descriptor_a)
    {
        gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), descriptor_a);
    }
    void set_pin_descriptor(Pin pin_a, const gpio::Descriptor<gpio::Mode::out>& descriptor_a)
    {
        gpio::configure_pin(this, static_cast<std::uint32_t>(pin_a), descriptor_a);
    }
    void set_pin_descriptor(Pin pin_a, const gpio::Descriptor<gpio::Mode::alternate>& descriptor_a)
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
    return { ll::gpio::registers<ll::gpio::A>(), static_cast<std::uint32_t>(pin_a) };
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
    std::uint32_t function_a,
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
    return { ll::gpio::registers<ll::gpio::B>(), static_cast<std::uint32_t>(pin_a) };
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
    std::uint32_t function_a,
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
    return { ll::gpio::registers<ll::gpio::C>(), static_cast<std::uint32_t>(pin_a) };
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
    std::uint32_t function_a,
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
    return { ll::gpio::registers<ll::gpio::D>(), static_cast<std::uint32_t>(pin_a) };
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
    std::uint32_t function_a,
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
    return { ll::gpio::registers<ll::gpio::F>(), static_cast<std::uint32_t>(pin_a) };
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
    std::uint32_t function_a,
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