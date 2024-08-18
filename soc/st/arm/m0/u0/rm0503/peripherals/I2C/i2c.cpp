/*
 *	Name: i2c.cpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

#if XMCU_SOC_ARCH_CORE_FAMILY == m0 && XMCU_SOC_VENDOR_FAMILY == stm32u0 && XMCU_SOC_VENDOR_FAMILY_RM == rm0503

// soc
#include <soc/st/arm/m0/u0/rm0503/peripherals/I2C/i2c.hpp>

namespace soc::st::arm::m0::u0::rm0503::peripherals {

void i2c::Peripheral<i2c::master>::set_descriptor(const i2c::Descriptor<i2c::master>& descriptor_a)
{
    this->cr1 = 0x0u;
    this->cr2 = 0x0u;

    this->timingr = descriptor_a.timing;
    this->cr1 = static_cast<std::uint32_t>(descriptor_a.analog_noise_filter) |
                static_cast<std::uint32_t>(descriptor_a.digital_noise_filter) | static_cast<std::uint32_t>(descriptor_a.fast_mode_plus) |
                static_cast<std::uint32_t>(descriptor_a.wakeup_from_stop) | (descriptor_a.digital_noise_filter << I2C_CR1_DNF_Pos);
    this->cr2 = (Address_kind::_10bit == descriptor_a.address_kind ? I2C_CR2_ADD10 : 0x0u);
}

void i2c::Peripheral<i2c::slave>::set_descriptor(const i2c::Descriptor<i2c::slave>& descriptor_a)
{
    this->cr1 = 0x0u;
    this->cr2 = 0x0u;

    this->timingr = descriptor_a.timing;
    this->cr1 = static_cast<std::uint32_t>(descriptor_a.analog_noise_filter) | static_cast<std::uint32_t>(descriptor_a.fast_mode_plus) |
                static_cast<std::uint32_t>(descriptor_a.general_call) | static_cast<std::uint32_t>(descriptor_a.wakeup_from_stop) |
                static_cast<std::uint32_t>(descriptor_a.address_kind) | (descriptor_a.digital_noise_filter << I2C_CR1_DNF_Pos);
    this->oar1 =
        I2C_OAR1_OA1EN | (Address_kind::_10bit == descriptor_a.address_kind ? ((descriptor_a.address & 0x3FFu) | I2C_OAR1_OA1MODE) :
                                                                              ((descriptor_a.address << 1u) & 0x7Fu));
}
} // namespace soc::st::arm::m0::u0::rm0503::peripherals
#endif