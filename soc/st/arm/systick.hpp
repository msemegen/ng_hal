#pragma once

/*
 */

// std
#include <cstdint>

// soc
#include <soc/macros.hpp>

// clang-format off
// CMSIS
#include DECORATE_INCLUDE_PATH(CMSIS_SOC_FILE)
// clang-format on

// soc
#include <soc/Non_copyable.hpp>
#include <soc/assert.hpp>
#include <soc/bit_flag.hpp>

// soc/st
#include <soc/st/arm/IRQ_priority.hpp>
#include <soc/st/arm/api.hpp>

namespace soc::st::arm {

struct systick : private non_constructible
{
    enum class Prescaler : std::uint32_t
    {
        _1 = SysTick_CTRL_CLKSOURCE_Msk,
        _8 = 0
    };

    template<api::traits traits_s> class Handler
        : private Non_copyable
        , private SysTick_Type
    {
    };

    class Controller
        : private Non_copyable
        , private SysTick_Type

    {
    public:
        template<api::traits traits_t>
        systick::Handler<traits_t>* enable(std::uint32_t a_reload, Prescaler a_prescaler) = delete;
        template<api::traits traits_t> systick::Handler<traits_t>*
        enable(std::uint32_t a_reload, Prescaler a_prescaler, const IRQ_priority priority_a) = delete;

        void disable()
        {
            this->LOAD = 0x0u;
            this->VAL  = 0x0u;
            this->CTRL = 0x0u;
        }

        bool is_enabled() const
        {
            return 0u != this->LOAD;
        }
    };

    static Controller* create()
    {
        return reinterpret_cast<Controller*>(SysTick_BASE);
    }
};
template<> inline systick::Handler<api::traits::sync>*
systick::Controller::enable<api::traits::sync>(std::uint32_t a_reload, systick::Prescaler a_prescaler)
{
    xmcu_assert(a_reload > 0);

    this->CTRL = 0x0u;
    this->LOAD = a_reload;
    this->VAL  = 0x0u;
    this->CTRL = static_cast<std::uint32_t>(a_prescaler);

    return reinterpret_cast<systick::Handler<api::traits::sync>*>(SysTick_BASE);
}
template<> inline systick::Handler<api::traits::async>*
systick::Controller::enable<api::traits::async>(std::uint32_t a_reload,
                                                systick::Prescaler a_prescaler,
                                                const IRQ_priority priority_a)
{
    xmcu_assert(a_reload > 0);

    this->CTRL = 0x0u;
    this->LOAD = a_reload;
    this->VAL  = 0x0u;
    this->CTRL = static_cast<std::uint32_t>(a_prescaler) | SysTick_CTRL_ENABLE_Msk;

    NVIC_SetPriority(
        SysTick_IRQn,
        NVIC_EncodePriority(NVIC_GetPriorityGrouping(), priority_a.preempt_priority, priority_a.sub_priority));

    return reinterpret_cast<systick::Handler<api::traits::async>*>(SysTick_BASE);
}

template<> class systick::Handler<api::traits::sync>
    : private Non_copyable
    , private SysTick_Type
{
public:
    void start()
    {
        bit_flag::set(&(this->CTRL), SysTick_CTRL_ENABLE_Msk);
    }

    void stop()
    {
        bit_flag::clear(&(this->CTRL), SysTick_CTRL_ENABLE_Msk);
    }

    void wait_for_reload() const
    {
        while (false == bit_flag::is(this->CTRL, SysTick_CTRL_COUNTFLAG_Msk)) continue;
    }

    std::uint32_t get_reload() const
    {
        return this->LOAD;
    }

    std::uint32_t get_value() const
    {
        return this->VAL;
    }

    bool is_started() const
    {
        return bit_flag::is(this->CTRL, SysTick_CTRL_ENABLE_Msk);
    }
};

template<> class systick::Handler<api::traits::async>
    : private Non_copyable
    , private SysTick_Type
{
public:
#if 1 == XMCU_ISR_CONTEXT
    void start(void* p_context_a);
#endif

#if 0 == XMCU_ISR_CONTEXT
    void start();
#endif
    void stop();

    std::uint32_t get_reload() const
    {
        return this->LOAD;
    }

    std::uint32_t get_value() const
    {
        return this->VAL;
    }

    bool is_started() const
    {
        return bit_flag::is(this->CTRL, SysTick_CTRL_ENABLE_Msk);
    }

    struct isr : private non_constructible
    {
#if 1 == XMCU_ISR_CONTEXT
        void static reload(Systick::Controller<api::traits::async>* p_systick_a, void* p_context_a);
#endif

#if 0 == XMCU_ISR_CONTEXT
        void static reload(systick::Handler<api::traits::async>* p_systick_a);
#endif
    };
};
} // namespace soc::st::arm