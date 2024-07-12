#pragma once

/*
 */

// std
#include <chrono>

// soc
#include <soc/Non_copyable.hpp>
#include <soc/macros.hpp>
#include <soc/st/arm/api.hpp>
#include <soc/st/arm/m0/u0/rm0503/peripherals/I2C/base.hpp>

// clang-format off
// CMSIS
#include DECORATE_INCLUDE_PATH(CMSIS_SOC_FILE)
// clang-format on

namespace soc::st::arm::m0::u0::rm0503::peripherals {
namespace ll {
struct i2c_clock : private non_constructible
{
    enum class Active_in_low_power
    {
        disable,
        enable
    };

    template<typename id_t, typename Source_t> static void enable(Active_in_low_power lp_a) = delete;
    template<typename id_t> static void disable() = delete;

    template<typename id_t> static bool is_enabled() = delete;
};

struct i2c : public i2c_base
{
    using clock = i2c_clock;

    struct Port : private Non_copyable
    {
        volatile std::uint32_t cr1;     /*!< I2C Control register 1,            Address offset: 0x00 */
        volatile std::uint32_t cr2;     /*!< I2C Control register 2,            Address offset: 0x04 */
        volatile std::uint32_t oar1;    /*!< I2C Own address 1 register,        Address offset: 0x08 */
        volatile std::uint32_t oar2;    /*!< I2C Own address 2 register,        Address offset: 0x0C */
        volatile std::uint32_t timingr; /*!< I2C Timing register,               Address offset: 0x10 */
    private:
        volatile std::uint32_t reserved; /*!< Reserved,                          Address offset: 0x14 */
    public:
        volatile std::uint32_t isr; /*!< I2C Interrupt and status register, Address offset: 0x18 */
        volatile std::uint32_t icr; /*!< I2C Interrupt clear register,      Address offset: 0x1C */
    private:
        volatile std::uint32_t reserved0; /*!< Reserved,                          Address offset: 0x20 */
    public:
        volatile std::uint32_t rxdr; /*!< I2C Receive data register,         Address offset: 0x24 */
        volatile std::uint32_t txdr; /*!< I2C Transmit data register,        Address offset: 0x28 */
    };
};
} // namespace ll

struct i2c : private non_constructible
{
    using clock = ll::i2c_clock;

    struct Descriptor
    {
        enum class Mode : std::uint64_t
        {
            master = 0x1u,
            slave = 0x2u
        };

        struct Master
        {
        };

        struct Slave
        {
            std::uint8_t address;
        };

        Mode mode;
    };

    struct traits : private non_constructible
    {
        template<auto sda_pin_t,
                 gpio::Descriptor<gpio::Mode::alternate> sda_descriptor_t,
                 auto scl_pin_t,
                 gpio::Descriptor<gpio::Mode::alternate> scl_descriptor_t>
        struct half_duplex
        {
            constexpr static auto sda_pin = sda_pin_t;
            constexpr static auto sda_descriptor = sda_descriptor_t;
            constexpr static auto scl_pin = scl_pin_t;
            constexpr static auto scl_descriptor = scl_descriptor_t;
        };
    };

    class Peripheral : private ll::i2c::Port
    {
    public:
        void set_descriptor(const Descriptor& descriptor_a) {}

        bool enable(std::chrono::milliseconds timeout_a);
        bool disable(std::chrono::milliseconds timeout_a);
    };

    template<api::traits trait_t> class Transceiver : private non_constructible
    {
    };

    template<typename id_t> [[nodiscard]] constexpr static Peripheral* create() = delete;

    template<typename id_t, typename transmission_mode_t> static void set_traits()
    {
        static_assert(get_allowed_sda_pins<id_t>().is(transmission_mode_t::sda_pin), "incorrect sda pin");
        static_assert(get_allowed_scl_pins<id_t>().is(transmission_mode_t::scl_pin), "incorrect scl pin");

        detail::sda_pin<id_t, transmission_mode_t::sda_descriptor, transmission_mode_t::sda_pin>::configure();
        detail::scl_pin<id_t, transmission_mode_t::scl_descriptor, transmission_mode_t::scl_pin>::configure();
    }
};

i2c::Descriptor::Mode operator|(i2c::Descriptor::Mode mode_a, const i2c::Descriptor::Master& master_a)
{
    assert(i2c::Descriptor::Mode::master == mode_a);
    return {};
}
i2c::Descriptor::Mode operator|(i2c::Descriptor::Mode mode_a, const i2c::Descriptor::Slave& slave_a)
{
    assert(i2c::Descriptor::Mode::slave == mode_a);
    return {};
}
} // namespace soc::st::arm::m0::u0::rm0503::peripherals