// hal
#include <xmcu/hal/IRQ_priority.hpp>
#include <xmcu/hal/Systick.hpp>
#include <xmcu/hal/api.hpp>
#include <xmcu/hal/clocks/pclk.hpp>
#include <xmcu/hal/clocks/sysclk.hpp>
#include <xmcu/hal/oscillators/hse.hpp>
#include <xmcu/hal/oscillators/hsi16.hpp>
#include <xmcu/hal/oscillators/msi.hpp>
#include <xmcu/hal/peripherals/GPIO.hpp>
#include <xmcu/hal/peripherals/i2c.hpp>
#include <xmcu/hal/peripherals/usart.hpp>
#include <xmcu/hal/stdglue.hpp>

// std
#include <cassert>
#include <charconv>
#include <chrono>
#include <sys/time.h>

using namespace xmcu::hal;
using namespace xmcu::hal::clocks;
using namespace xmcu::hal::oscillators;
using namespace xmcu::hal::peripherals;

template<typename Duration_t> void delay(Duration_t timeout_a)
{
    const auto end = std::chrono::steady_clock::now() + timeout_a;
    while (end >= std::chrono::steady_clock::now()) continue;
}

#ifndef NDEBUG
void stdglue::assert::handler::output(std::string_view message_a, void* p_context_a)
{
    auto* p_usart = reinterpret_cast<usart::Transceiver<api::traits::sync>*>(p_context_a);

    p_usart->write(message_a);
}
void stdglue::assert::handler::output(std::int32_t line_a, void* p_context_a)
{
    auto* p_usart = reinterpret_cast<usart::Transceiver<api::traits::sync>*>(p_context_a);

    char buff[7u];
    std::to_chars(buff, buff + 7u, line_a);

    p_usart->write(std::string_view { buff });
}
#endif

int main()
{
    using namespace std::chrono_literals;

    systick::Peripheral* p_systick = systick::create();

    hsi16::set_descriptor({ .start_from_stop = hsi16::Descriptor::Start_from_stop::disable,
                            .power = hsi16::Descriptor::Power::only_in_run,
                            .trimm = 0x0u,
                            .calibration = 0x0u });
    hsi16::enable();
    while (false == hsi16::is_ready()) continue;

    sysclk::set_source<hsi16>();
    while (false == sysclk::is_source<hsi16>()) continue;

    msi::disable();
    hse::set_traits<hse::traits::xtal<gpio::F::Pin::_0, gpio::F::Pin::_1>>();
    hse::enable(4'000'000u);

    p_systick->set_descriptor({ .prescaler = systick::Descriptor::Prescaler::_1, .reload = (sysclk::get_frequency_Hz() / 1000u) - 1u });

    auto* p_async_systick = p_systick->get_view<systick::Tick_counter<api::traits::async>>();

    if (nullptr != p_async_systick)
    {
#if 1 == XMCU_ISR_CONTEXT
        p_async_systick->start({ .preempt_priority = 1u, .sub_priority = 1u }, nullptr);
#else
        p_async_systick->start({ .preempt_priority = 1u, .sub_priority = 1u });
#endif
        stdglue::steady_clock::set_source(p_async_systick);

        gpio::clock::enable<gpio::A>();

        // compile time chceck for pins and basic configuration
        usart::clock::enable<usart::_2, sysclk>(usart::clock::Stop_mode_activity::disable);
        usart::set_traits<
            usart::_2,
            usart::traits::full_duplex<gpio::A::Pin::_3,
                                       gpio::Descriptor<gpio::Mode::alternate> {
                                           .type = gpio::Type::push_pull, .pull = gpio::Pull::up, .speed = gpio::Speed::low },
                                       gpio::A::Pin::_2,
                                       gpio::Descriptor<gpio::Mode::alternate> {
                                           .type = gpio::Type::push_pull, .pull = gpio::Pull::none, .speed = gpio::Speed::low }>>();

        // i2c::clock::enable<i2c::_1, sysclk>(i2c::clock::Stop_mode_activity::disable);
        // i2c::set_traits<
        //     i2c::_1,
        //     i2c::traits::half_duplex<gpio::A::Pin::_10,
        //                              gpio::Descriptor<gpio::Mode::alternate> {
        //                                  .type = gpio::Type::open_drain, .pull = gpio::Pull::up, .speed = gpio::Speed::high },
        //                              gpio::A::Pin::_9,
        //                              gpio::Descriptor<gpio::Mode::alternate> {
        //                                  .type = gpio::Type::open_drain, .pull = gpio::Pull::up, .speed = gpio::Speed::high }>>();

        usart::Peripheral* p_usart2 = usart::interface<usart::_2>(); // TODO: interace, like in GPIO

        // transmission configuration
        p_usart2->set_descriptor(
            usart::Descriptor { .fifo = usart::Descriptor::Fifo::disable,
                                .oversampling = usart::Descriptor::Oversampling::_16,
                                .sampling = usart::Descriptor::Sampling::three_sample_bit,
                                .mute = usart::Descriptor::Mute::disable,
                                .baudrate = 115200u,
                                .clock { .clk_freq_Hz = sysclk::get_frequency_Hz(), .prescaler = usart::Descriptor::Clock::Prescaler::_1 },
                                .frame { .word_length = usart::Descriptor::Frame::Word_length::_8_bit,
                                         .parity = usart::Descriptor::Frame::Parity::none,
                                         .stop_bits = usart::Descriptor::Frame::Stop_bits::_1,
                                         .msb_first = usart::Descriptor::Frame::MSB_first::disable,
                                         .inversion = usart::Descriptor::Frame::Inversion::disable } });

        gpio::Pad led;
        gpio::interface<gpio::A>()->enable(
            gpio::A::Pin::_5,
            gpio::Descriptor<gpio::Mode::out> { .type = gpio::Type::push_pull, .pull = gpio::Pull::none, .speed = gpio::Speed::low },
            &led);

        bool usart1_enabled = p_usart2->enable(usart::Mode::rx | usart::Mode::tx, usart::Stop_mode_activity::disable, 10ms);

        // if (true == usart1_enabled)
        //{
        //     // sync transmission view
        //     usart::Transceiver<api::traits::sync>* p_usart2_comm = p_usart2->get_view<usart::Transceiver<api::traits::sync>>();
        //     stdglue::assert::set_context(p_usart2_comm);

        //    // echo
        //    while (true)
        //    {
        //        char c = '\0';

        //        p_usart2_comm->read(std::span { &c, 1u });
        //        p_usart2_comm->write(std::span { &c, 1u });
        //        led.toggle();

        //        assert(c != 't'); // assert test
        //    }
        //}
        // else
        {
            while (true)
            {
                led.toggle();
                delay(1s);
            }
        }
    }

    while (true) continue;
}