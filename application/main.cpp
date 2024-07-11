// hal
#include <hal/IRQ_priority.hpp>
#include <hal/Systick.hpp>
#include <hal/api.hpp>
#include <hal/clocks/pclk.hpp>
#include <hal/clocks/sysclk.hpp>
#include <hal/oscillators/hsi16.hpp>
#include <hal/oscillators/msi.hpp>
#include <hal/peripherals/GPIO.hpp>
#include <hal/peripherals/usart.hpp>
#include <hal/stdglue.hpp>

// std
#include <cassert>
#include <charconv>
#include <chrono>

using namespace hal;
using namespace hal::clocks;
using namespace hal::oscillators;
using namespace hal::peripherals;

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

    p_systick->set_descriptor({ .prescaler = systick::Descriptor::Prescaler::_1, .reload = sysclk::get_frequency_Hz() - 1u });

    auto* p_async_systick = p_systick->get_view<systick::Tick_counter<api::traits::async>>();

    if (nullptr != p_async_systick)
    {
        p_async_systick->start({ .preempt_priority = 1u, .sub_priority = 1u });
        stdglue::steady_clock::set_source(p_async_systick);

        usart::Peripheral* p_usart2 = usart::create<usart::_2>();

        gpio::clock::enable<gpio::A>();
        usart::clock::enable<usart::_2, sysclk>(usart::clock::Active_in_low_power::disable);

        p_usart2->set_descriptor(
            usart::Descriptor { .fifo = usart::Descriptor::Fifo::disable,
                                .oversampling = usart::Descriptor::Oversampling::_16,
                                .sampling = usart::Descriptor::Sampling::three_sample_bit,
                                .mute = usart::Descriptor::Mute::none,
                                .auto_baudrate = usart::Descriptor::Auto_baudrate::disable | 115200u,
                                .clock { .clk_freq_Hz = sysclk::get_frequency_Hz(), .prescaler = usart::Descriptor::Clock::Prescaler::_1 },
                                .frame { .word_length = usart::Descriptor::Frame::Word_length::_8_bit,
                                         .parity = usart::Descriptor::Frame::Parity::none,
                                         .stop_bits = usart::Descriptor::Frame::Stop_bits::_1,
                                         .msb_first = usart::Descriptor::Frame::MSB_first::disable,
                                         .inversion = usart::Descriptor::Frame::Inversion::disable } });

        p_usart2->set_traits<
            usart::_2,
            usart::traits::full_duplex<gpio::A::Pin::_3,
                                       gpio::Descriptor<gpio::Mode::alternate> {
                                           .type = gpio::Type::push_pull, .pull = gpio::Pull::up, .speed = gpio::Speed::low },
                                       gpio::A::Pin::_2,
                                       gpio::Descriptor<gpio::Mode::alternate> {
                                           .type = gpio::Type::push_pull, .pull = gpio::Pull::none, .speed = gpio::Speed::low }>>();

        bool usart1_enabled = p_usart2->enable(usart::Mode::rx | usart::Mode::tx, 10ms);

        if (true == usart1_enabled)
        {
            stdglue::assert::set_context(p_usart2);

            gpio::Pad led_pad;

            gpio::interface<gpio::A>()->enable(
                gpio::A::Pin::_5,
                gpio::Descriptor<gpio::Mode::out> { .type = gpio::Type::push_pull, .pull = gpio::Pull::none, .speed = gpio::Speed::low },
                &led_pad);

            usart::Transceiver<api::traits::sync>* p_usart2_comm = p_usart2->get_view<usart::Transceiver<api::traits::sync>>();

            stdglue::assert::set_context(p_usart2_comm);

            // echo
            while (true)
            {
                char c = '\0';

                p_usart2_comm->read(std::span { &c, 1u });
                p_usart2_comm->write(std::span { &c, 1u });
                led_pad.toggle();

                assert(c != 't');
            }

            while (true)
                ;
        }
        else
        {
            while (true)
                ;
        }

        while (true)
        {
            delay(1000ms);
            // led_pad.toggle();
        }
    }

    while (true) continue;
}