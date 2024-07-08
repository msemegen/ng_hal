#pragma once

/*
 */

// std
#include <cassert>
#include <cstdint>

// soc
#include <soc/macros.hpp>

// clang-format off
// CMSIS
#include DECORATE_INCLUDE_PATH(CMSIS_SOC_FILE)
// clang-format on

// soc
#include <soc/Non_copyable.hpp>
#include <soc/bit_flag.hpp>

// soc/st
#include <soc/st/arm/IRQ_priority.hpp>
#include <soc/st/arm/api.hpp>

namespace soc::st::arm {

struct systick : private non_constructible
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
        : private Non_copyable
        , private SysTick_Type
    {
    };

    class Peripheral
        : private Non_copyable
        , private SysTick_Type

    {
    public:
        void set_descriptor(const Descriptor& descriptor_a)
        {
            assert(descriptor_a.reload > 0 && descriptor_a.reload <= 0xFFF'FFFu);

            this->CTRL = 0x0u;
            this->LOAD = descriptor_a.reload;
            this->VAL = 0x0u;
            this->CTRL = static_cast<std::uint32_t>(descriptor_a.prescaler);
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

template<> class systick::Tick_counter<api::traits::async>
    : private Non_copyable
    , private SysTick_Type
{
public:
#if 1 == XMCU_ISR_CONTEXT
    void start(const IRQ_priority priority_a, void* p_context_a);
#endif

#if 0 == XMCU_ISR_CONTEXT
    void start(const IRQ_priority priority_a);
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
        void static reload(Systick::Tick_counter<api::traits::async>* p_systick_a, void* p_context_a);
#endif

#if 0 == XMCU_ISR_CONTEXT
        void static reload(systick::Tick_counter<api::traits::async>* p_systick_a);
#endif
    };
};
} // namespace soc::st::arm