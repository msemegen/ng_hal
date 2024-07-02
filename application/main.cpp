// hal
#include <hal/IRQ_priority.hpp>
#include <hal/Systick.hpp>
#include <hal/api.hpp>
#include <hal/clocks/pclk.hpp>
#include <hal/peripherals/GPIO.hpp>
#include <hal/peripherals/usart.hpp>
#include <hal/stdglue.hpp>

// std
#include <chrono>

using namespace hal;
using namespace hal::clocks;
using namespace hal::peripherals;

namespace {
volatile std::uint64_t systick_count = 0x0u;
}

template<typename Duration_t> void delay(Duration_t timeout_a)
{
    const auto end = std::chrono::steady_clock::now() + timeout_a;
    while (end >= std::chrono::steady_clock::now()) continue;
}

int main()
{
    using namespace std::chrono_literals;

    systick::Controller* p_systick = systick::create();

    systick::Handler<api::traits::async>* p_async_systick = p_systick->enable<api::traits::async>(
        4000u - 1u, systick::Prescaler::_1, IRQ_priority { .preempt_priority = 1u, .sub_priority = 1u });

    if (nullptr != p_async_systick)
    {
        stdglue::set_steady_clock_source(p_async_systick);

        gpio::Pad led_pad;

        gpio::clock::enable<gpio::A>();
        gpio::interface<gpio::A>()->enable(
            gpio::A::Pin::_5,
            gpio::Descriptor<gpio::Mode::out> { .type = gpio::Type::push_pull, .pull = gpio::Pull::none, .speed = gpio::Speed::low },
            &led_pad);

        // led_pad.toggle();

        p_async_systick->start();

        gpio::interface<gpio::A>()->write(gpio::A::Pin::_5, gpio::Level::high);

        // usart::clock::enable();
        // usart::traits::synchronous<gpio::A::Pin::_8, usart::traits::master>,
        // usart::traits::hardware_flow_control<usart::traits::cts<gpio::A::Pin::_11>>

        /*usart::traits::hardware_flow_control<usart::traits::cts<gpio::A::Pin::_11>>*/
        usart::Peripheral* p_usart2 = usart::create<usart::_2>();

        usart::clock::enable<usart::_2, pclk>(usart::clock::Active_in_low_power::disable);
        p_usart2->set_traits<
            usart::_2,
            usart::traits::full_duplex<gpio::A::Pin::_3,
                                       gpio::Descriptor<gpio::Mode::alternate> {
                                           .type = gpio::Type::push_pull, .pull = gpio::Pull::up, .speed = gpio::Speed::low },
                                       gpio::A::Pin::_2,
                                       gpio::Descriptor<gpio::Mode::alternate> {
                                           .type = gpio::Type::push_pull, .pull = gpio::Pull::none, .speed = gpio::Speed::low }>>();

        p_usart2->init(usart::Clock { .clk_freq_Hz = SystemCoreClock, .prescaler = usart::Clock::Prescaler::_1 },
                       usart::Descriptor { .fifo = usart::Descriptor::Fifo::disable,
                                           .oversampling = usart::Descriptor::Oversampling::_16,
                                           .sampling = usart::Descriptor::Sampling::three_sample_bit,
                                           .mute = usart::Descriptor::Mute::none,
                                           .auto_baudrate = usart::Descriptor::Auto_baudrate::disable | 115200u,
                                           .frame { .word_length = usart::Descriptor::Frame::Word_length::_8_bit,
                                                    .parity = usart::Descriptor::Frame::Parity::none,
                                                    .stop_bits = usart::Descriptor::Frame::Stop_bits::_1,
                                                    .msb_first = usart::Descriptor::Frame::MSB_first::disable,
                                                    .inversion = usart::Descriptor::Frame::Inversion::disable } });

        bool usart1_enabled = p_usart2->enable(usart::Mode::rx | usart::Mode::tx, 10ms);

        if (true == usart1_enabled)
        {
            usart::Transceiver<api::traits::sync>* p_usart2_comm = p_usart2->get_view<usart::Transceiver<api::traits::sync>>();

            // echo
            while (true)
            {
                char c = '\0';

                p_usart2_comm->read(std::span { &c, 1u });
                p_usart2_comm->write(std::span { &c, 1u });
                led_pad.toggle();
            }

            while (true)
                ;
        }
        else
        {
            while (true)
                ;
        }

        /*
         *   set_hw_desc<>
         *   init(...)
         *
         *   enable();
         *   disable();
         */

        // p_usart->init();
        // p_usart1->enable(...);

        // const auto pin = 0x1u << 5u;

        //   USART* p_usart = api::interface<usart::_1<usart::traits::full_duplex<gpio::A::Pin::_3, gpio::A::Pin::_2>,
        //                                             usart::traits::software_flow_control>>();
        //
        //   USART::Controller<api::traits::async>* p_async_usart = p_usart->enable<api::traits::async>();

        // p_async_usart->receive();

        // std::uint32_t retx = 0;

        //{
        //    ret = ret;
        //}

        // retx = retx;

        // ll::usart::Port p;
        // p.cr1.set(ll::usart::Port::CR1::Flag::enable | ll::usart::Port::CR1::Flag::low_power);

        while (true)
        {
            delay(1000ms);
            // led_pad.toggle();
        }
    }

    while (true) continue;
}