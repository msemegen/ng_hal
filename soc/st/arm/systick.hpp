#pragma once

/*
 *	Name: systick.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <cassert>
#include <cstdint>

// clang-format off
// xmcu
#include <xmcu/macros.hpp>
// CMSIS
#include DECORATE_INCLUDE_PATH(CMSIS_SOC_FILE)
// clang-format on

// xmcu
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>
#include <xmcu/non_copyable.hpp>

// soc
#include <soc/st/arm/IRQ_priority.hpp>
#include <soc/st/arm/api.hpp>

namespace soc::st::arm {
namespace ll {
struct systick : private xmcu::non_constructible
{
    struct Port
    {
        volatile std::uint32_t ctrl;        /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
        volatile std::uint32_t load;        /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
        volatile std::uint32_t val;         /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
        volatile const std::uint32_t calib; /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
    };
};
} // namespace ll
struct systick : private xmcu::non_constructible
{
    struct Descriptor
    {
        enum class Prescaler : std::uint32_t
        {
            _1 = SysTick_CTRL_CLKSOURCE_Msk,
            _8 = 0
        };

        Prescaler prescaler;
        std::uint32_t reload = 0u;
    };

    template<api::traits traits_t> class Tick_counter
        : private xmcu::non_constructible
        , private ll::systick::Port
    {
    };

    class Peripheral
        : private xmcu::non_copyable
        , private ll::systick::Port

    {
    public:
        void set_descriptor(const Descriptor& descriptor_a)
        {
            assert(descriptor_a.reload > 0 && descriptor_a.reload <= 0xFFF'FFFu);

            this->ctrl = 0x0u;
            this->load = descriptor_a.reload;
            this->val = 0x0u;
            this->ctrl = static_cast<std::uint32_t>(descriptor_a.prescaler);
        }

        Descriptor get_descriptor() const
        {
            return { .prescaler = static_cast<Descriptor::Prescaler>(xmcu::bit::flag::get(this->ctrl, SysTick_CTRL_CLKSOURCE_Msk)),
                     .reload = this->load };
        }

        template<typename Type_t> Type_t* get_view() const = delete;
    };

    static Peripheral* create()
    {
        return reinterpret_cast<Peripheral*>(SysTick_BASE);
    }
};

template<> inline systick::Tick_counter<api::traits::sync>* systick::Peripheral::get_view() const
{
    return reinterpret_cast<systick::Tick_counter<api::traits::sync>*>(SysTick_BASE);
}
template<> inline systick::Tick_counter<api::traits::async>* systick::Peripheral::get_view() const
{
    return reinterpret_cast<systick::Tick_counter<api::traits::async>*>(SysTick_BASE);
}

template<> class systick::Tick_counter<api::traits::sync>
    : private xmcu::non_copyable
    , private ll::systick::Port
{
public:
    Descriptor get_descriptor() const
    {
        return { .prescaler = static_cast<Descriptor::Prescaler>(xmcu::bit::flag::get(this->ctrl, SysTick_CTRL_CLKSOURCE_Msk)),
                 .reload = this->load };
    }

    void start()
    {
        xmcu::bit::flag::set(&(this->ctrl), SysTick_CTRL_ENABLE_Msk);
    }

    void stop()
    {
        xmcu::bit::flag::clear(&(this->ctrl), SysTick_CTRL_ENABLE_Msk);
    }

    void wait_for_reload() const
    {
        while (false == xmcu::bit::flag::is(this->ctrl, SysTick_CTRL_COUNTFLAG_Msk)) continue;
    }

    std::uint32_t get_value() const
    {
        return this->val;
    }

    bool is_started() const
    {
        return xmcu::bit::flag::is(this->ctrl, SysTick_CTRL_ENABLE_Msk);
    }
};

template<> class systick::Tick_counter<api::traits::async>
    : private xmcu::non_copyable
    , private ll::systick::Port
{
public:
    Descriptor get_descriptor() const
    {
        return { .prescaler = static_cast<Descriptor::Prescaler>(xmcu::bit::flag::get(this->ctrl, SysTick_CTRL_CLKSOURCE_Msk)),
                 .reload = this->load };
    }

#if 1 == XMCU_ISR_CONTEXT
    void start(const IRQ_priority& priority_a, void* p_context_a);
#endif

#if 0 == XMCU_ISR_CONTEXT
    void start(const IRQ_priority& priority_a);
#endif
    void stop();

    bool is_started() const
    {
        return xmcu::bit::flag::is(this->ctrl, SysTick_CTRL_ENABLE_Msk);
    }

    struct isr : private non_constructible
    {
#if 1 == XMCU_ISR_CONTEXT
        void static on_reload(systick::Tick_counter<api::traits::async>* p_systick_a, std::uint32_t value_a, void* p_context_a);
#endif

#if 0 == XMCU_ISR_CONTEXT
        void static on_reload(systick::Tick_counter<api::traits::async>* p_systick_a, std::uint32_t value_a);
#endif
    };
};
} // namespace soc::st::arm