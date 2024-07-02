/*
 *	Name: gpio.cpp
 *
 *   Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *   Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#if XMCU_SOC_ARCH_CORE_FAMILY == m0 && XMCU_SOC_VENDOR_FAMILY == stm32u0 && XMCU_SOC_VENDOR_FAMILY_RM == rm0503

// soc
#include <soc/st/arm/m0/u0/rm0503/peripherals/GPIO/gpio.hpp>

namespace soc::st::arm::m0::u0::rm0503::peripherals {
void gpio::enable_pin(ll::gpio::Port* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::out>& desc_a)
{
    xmcu_assert(various::get_enum_incorrect_value<Pull>() != desc_a.pull);
    xmcu_assert(various::get_enum_incorrect_value<Speed>() != desc_a.speed);
    xmcu_assert(various::get_enum_incorrect_value<Type>() != desc_a.type);

    const std::uint32_t clear_flag_2bit = 0x3u << (pin_a * 2);

    bit_flag::set(&(p_port_a->ospeedr), clear_flag_2bit, static_cast<std::uint32_t>(desc_a.speed) << (pin_a * 2u));
    bit_flag::set(&(p_port_a->pupdr), clear_flag_2bit, static_cast<std::uint32_t>(desc_a.pull) << (pin_a * 2u));
    bit_flag::set(&(p_port_a->moder), clear_flag_2bit, 0x1u << (pin_a * 2u));
    bit_flag::set(&(p_port_a->otyper), 0x1u << pin_a, static_cast<std::uint32_t>(desc_a.type) << pin_a);
}

void gpio::enable_pin(ll::gpio::Port* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::in>& desc_a)
{
    xmcu_assert(various::get_enum_incorrect_value<Pull>() != desc_a.pull);

    bit_flag::set(&(p_port_a->pupdr), 0x3u << (pin_a * 2u), static_cast<std::uint32_t>(desc_a.pull) << (pin_a * 2u));
    bit_flag::clear(&(p_port_a->moder), 0x3u << (pin_a * 2u));
}

void gpio::enable_pin(ll::gpio::Port* p_port_a, std::uint32_t pin_a, const gpio::Descriptor<gpio::Mode::analog>& desc_a)
{
    xmcu_assert(various::get_enum_incorrect_value<Pull>() != desc_a.pull);

    bit_flag::set(&(p_port_a->pupdr), 0x3u << (pin_a * 2u), static_cast<std::uint32_t>(desc_a.pull) << (pin_a * 2u));
    bit_flag::set(&(p_port_a->moder), 0x3u << (pin_a * 2u), 0x3u << (pin_a * 2u));
}

void gpio::enable_pin(ll::gpio::Port* p_port_a, std::uint32_t pin_a, std::uint8_t function_a, const gpio::Descriptor<gpio::Mode::alternate>& desc_a)
{
    const std::uint32_t clear_flag_2bit = 0x3u << (pin_a * 2);

    bit_flag::set(&(p_port_a->ospeedr), clear_flag_2bit, static_cast<std::uint32_t>(desc_a.speed) << (pin_a * 2u));
    bit_flag::set(&(p_port_a->pupdr), clear_flag_2bit, static_cast<std::uint32_t>(desc_a.pull) << (pin_a * 2u));
    bit_flag::set(&(p_port_a->moder), clear_flag_2bit, 0x2u << (pin_a * 2u));
    bit_flag::set(&(p_port_a->otyper), 0x1u << pin_a, static_cast<std::uint32_t>(desc_a.type) << pin_a);

    const std::uint32_t af_register_index = pin_a >> 3u;
    std::uint32_t af_register = p_port_a->afr[af_register_index];

    af_register &= ~(0xFu << ((pin_a - (af_register_index * 8u)) * 4u));
    af_register |= static_cast<std::uint32_t>(function_a) << ((pin_a - (af_register_index * 8u)) * 4u);

    p_port_a->afr[af_register_index] = af_register;
}

} // namespace soc::st::arm::m0::u0::rm0503::peripherals

#endif