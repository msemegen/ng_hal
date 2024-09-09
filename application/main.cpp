// hal
#include <xmcu/Scoped_guard.hpp>
#include <xmcu/hal/IRQ_priority.hpp>
#include <xmcu/hal/Systick.hpp>
#include <xmcu/hal/api.hpp>
#include <xmcu/hal/clocks/pclk.hpp>
#include <xmcu/hal/clocks/sysclk.hpp>
#include <xmcu/hal/nvic.hpp>
#include <xmcu/hal/oscillators/hse.hpp>
#include <xmcu/hal/oscillators/hsi16.hpp>
#include <xmcu/hal/oscillators/msi.hpp>
#include <xmcu/hal/oscillators/pll.hpp>
#include <xmcu/hal/peripherals/gpio.hpp>
#include <xmcu/hal/peripherals/i2c.hpp>
#include <xmcu/hal/peripherals/usart.hpp>
#include <xmcu/stdglue.hpp>

// std
#include <cassert>
#include <charconv>
#include <chrono>
#include <format>
#include <iostream>
#include <sys/time.h>
#include <thread>

using namespace xmcu::hal;
using namespace xmcu::hal::clocks;
using namespace xmcu::hal::oscillators;
using namespace xmcu::hal::peripherals;

#ifndef NDEBUG
void xmcu::stdglue::assert::handler::output(std::string_view message_a, void* p_context_a)
{
    auto* p_usart = reinterpret_cast<usart::Transceiver<api::traits::sync>*>(p_context_a);

    p_usart->transmit(message_a);
}
void xmcu::stdglue::assert::handler::output(std::int32_t line_a, void* p_context_a)
{
    auto* p_usart = reinterpret_cast<usart::Transceiver<api::traits::sync>*>(p_context_a);

    char buff[7u];
    std::to_chars(buff, buff + 7u, line_a);

    p_usart->transmit(std::string_view { buff });
}
#endif

volatile std::uint32_t flag = 0x0u;
char c[5];
volatile std::size_t i = 0;
gpio::Pad led;
void usart::Transceiver<api::traits::async>::handler::on_receive(std::uint32_t word_a,
                                                                 usart::Error errors_a,
                                                                 usart::Transceiver<api::traits::async>* p_this)
{
    if (usart::Error::none == errors_a)
    {
        c[4] = static_cast<char>(word_a);
        flag = 0x1u;
    }
}

std::uint32_t usart::Transceiver<api::traits::async>::handler::on_transmit(usart::Transceiver<api::traits::async>* p_this)
{
    if (i < 5u)
    {
        i = i + 1u;
        return c[i - 1u];
    }

    return no_data_to_transmit;
}

void usart::Transceiver<api::traits::async>::handler::on_event(usart::Event events_a,
                                                               usart::Error errors_a,
                                                               usart::Transceiver<api::traits::async>* p_this)
{
    if (usart::Event::transfer_complete == (events_a & usart::Event::transfer_complete))
    {
        p_this->transmit_stop();
        i = 0u;
    }
    if (usart::Event::idle == (events_a & usart::Event::idle))
    {
        led.toggle();
    }
}

void gpio::async::handler::on_fall(std::uint32_t pin_a)
{
    if (13u == pin_a)
    {
        led.toggle();
    }
}
// void gpio::async::handler::on_rise(std::uint32_t pin_a)
//{
//     auto x = 0;
//     x = x;
//     gpio::port<gpio::A, api::traits::sync>()->toggle(gpio::A::_5);
// }

int main()
{
    using namespace xmcu;
    using namespace std::chrono_literals;

    nvic::set_descriptor({ .grouping = nvic::Descriptor::Grouping::_2 });
    nvic::enable();

    systick::Peripheral* p_systick = systick::create();

    hsi16::set_descriptor({ .start_from_stop = hsi16::Descriptor::Start_from_stop::disable,
                            .power = hsi16::Descriptor::Power::only_in_run,
                            .trimm = 0x0u,
                            .calibration = 0x0u });
    hsi16::enable();
    while (false == hsi16::is_ready()) continue;

    sysclk::set_traits<sysclk::traits::source<hsi16>>();
    while (false == sysclk::is_trait<sysclk::traits::source<hsi16>>()) continue;

    msi::disable();
    hse::set_traits<hse::traits::xtal<gpio::F::_0, gpio::F::_1>>();
    hse::enable(4'000'000u);

    pll::r.set_descriptor({});
    pll::p.set_descriptor({});

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

        // enabling GPIO A and C clock
        gpio::clock::enable<gpio::A>();
        gpio::clock::enable<gpio::C>();

        // using ll_gpio = peripherals::ll::gpio;
        //
        // ll_gpio::Port* p_port = ll_gpio::port<ll_gpio::A>();
        // p_port->moder.set(ll_gpio::Moder::analog << 3u, ll_gpio::Moder::analog << 4u, ll_gpio::Moder::analog << 6u);

        // enabling global GPIO interrupts
        gpio::async::enable({ .preempt_priority = 0x1u, .sub_priority = 0x1u });

        // getting access to GPIO A port
        gpio::Port<gpio::A, api::traits::sync>* p_gpio_A = gpio::port<gpio::A, api::traits::sync>();

        // enabling PA5
        p_gpio_A->set_pin_descriptor(
            gpio::A::_5,
            gpio::Descriptor<gpio::Mode::out> { .type = gpio::Type::push_pull, .pull = gpio::Pull::none, .speed = gpio::Speed::low });

        // view for PA5 pad
        led = p_gpio_A->view<gpio::Pad>(gpio::A::_5);

        gpio::Port<gpio::C, api::traits::sync>* p_gpio_C = gpio::port<gpio::C, api::traits::sync>();

        // setting PC13 properties (no need for creating separate port object)
        gpio::port<gpio::C, api::traits::async>()->set_pin_descriptor(gpio::C::_13,
                                                                      gpio::Descriptor<gpio::Mode::in> { .pull = gpio::Pull::up });

        // checking if EXTI line for PC13 is free
        if (false == gpio::port<gpio::C, api::traits::async>()->is_taken(gpio::C::_13))
        {
            // enabling interrupt handling for falling edge
            gpio::port<gpio::C, api::traits::async>()->start(gpio::C::_13, gpio::Edge::falling);
        }

        // compile time chceck for pins and basic configuration
        usart::clock::enable<usart::_2, sysclk>(usart::clock::Stop_mode_activity::disable);
        usart::set_traits<
            usart::_2,
            usart::traits::full_duplex<gpio::A::_3,
                                       gpio::Descriptor<gpio::Mode::alternate> {
                                           .type = gpio::Type::push_pull, .pull = gpio::Pull::up, .speed = gpio::Speed::low },
                                       gpio::A::_2,
                                       gpio::Descriptor<gpio::Mode::alternate> {
                                           .type = gpio::Type::push_pull, .pull = gpio::Pull::none, .speed = gpio::Speed::low }>>();

        // i2c::clock::enable<i2c::_1, sysclk>(i2c::clock::Stop_mode_activity::disable);
        // i2c::set_traits<
        //     i2c::_1,
        //     i2c::traits::half_duplex<gpio::A::_10,
        //                              gpio::Descriptor<gpio::Mode::alternate> {
        //                                  .type = gpio::Type::open_drain, .pull = gpio::Pull::up, .speed = gpio::Speed::high },
        //                              gpio::A::_9,
        //                              gpio::Descriptor<gpio::Mode::alternate> {
        //                                  .type = gpio::Type::open_drain, .pull = gpio::Pull::up, .speed = gpio::Speed::high }>>();

        // i2c::Peripheral<i2c::master>* p_i2c_bus = i2c::peripheral<i2c::_1, i2c::master>();
        // p_i2c_bus->set_descriptor({ .fast_mode_plus = i2c::Fast_mode_plus::disable,
        //                             .analog_noise_filter = i2c::Analog_noise_filter::disable,
        //                             .wakeup_from_stop = i2c::Wakeup_from_stop::disable,
        //                             .address_kind = i2c::Address_kind::_7bit,
        //                             .timing = 0x00503D5Au,
        //                             .digital_noise_filter = 0x0u });

        /*p_i2c_bus->enable(10ms);

        auto i2c_transceview = p_i2c_bus->view<i2c::Transceiver<api::traits::sync, i2c::master>>();

        const std::uint8_t d = 0x75;
        auto i2c_ret = i2c_transceview->transmit(0xD0u, std::span<const std::uint8_t> { &d, 1u });

        if (i2c::Error::none == i2c_ret.second)
        {
            std::uint8_t r = 0;
            i2c_ret = i2c_transceview->receive(0xD0u, std::span<std::uint8_t> { &r, 1 });

            if (0xD0u == (r << 1u))
            {
                gpio::port<gpio::A, api::traits::sync>()->toggle(gpio::A::_5);
            }
            else
            {
                while (true)
                    ;
            }
        }
        else
        {
            while (true)
                ;
        }

        i2c_ret = i2c_ret;*/

        // p_i2c_bus->set_descriptor({});
        // p_i2c_bus->enable(10ms);

        // auto i2c_transc = p_i2c_bus->view<i2c::Transceiver<api::traits::sync, i2c::master>>();

        // std::uint8_t data[3];
        // i2c_transc->transmit(0x11u | i2c::Address_kind::_7bit, data);

        usart::Peripheral* p_usart2 = usart::peripheral<usart::_2>();

        // auto xyz = gpio::port<gpio::A, api::traits::sync>();
        // xyz->set_pin_descriptor(gpio::A::_0, gpio::Descriptor<gpio::Mode::analog> {});

        // transmission configuration
        p_usart2->set_descriptor(usart::Descriptor { .prescaler = usart::Prescaler::_1,
                                                     .fifo = usart::Fifo::disable,
                                                     .oversampling = usart::Oversampling::_16,
                                                     .sampling = usart::Sampling::three_sample_bit,
                                                     .mute = usart::Mute::disable,
                                                     .baudrate = 115200u,
                                                     .frame { .word_length = usart::Frame::Word_length::_8_bit,
                                                              .parity = usart::Frame::Parity::none,
                                                              .stop_bits = usart::Frame::Stop_bits::_1,
                                                              .msb_first = usart::Frame::MSB_first::disable,
                                                              .inversion = usart::Frame::Inversion::disable } });

        //.clock { .clk_freq_Hz = sysclk::get_frequency_Hz(), .prescaler = usart::Clock::Prescaler::_1 },

        bool usart1_enabled = p_usart2->enable(usart::Mode::rx | usart::Mode::tx, usart::Stop_mode_activity::disable, 10ms);

        if (true == usart1_enabled)
        {
            // sync transmission view
            usart::Transceiver<api::traits::sync>* p_usart2_comm = p_usart2->view<usart::Transceiver<api::traits::sync>>();
            stdglue::assert::set_context(p_usart2_comm);

            auto usart_async = p_usart2->view<usart::Transceiver<api::traits::async>>();

            usart_async->enable({ 0x0u, 0x0u });
            usart_async->receive_start();
            usart_async->events_start(usart::Event::transfer_complete | usart::Event::idle);

            // led.write(gpio::Level::high);
            // gpio::port<gpio::A, api::traits::sync>()->write(gpio::A::_5, gpio::Level::high);

            // echo
            c[0] = 'A';
            c[1] = 'B';
            c[2] = 'C';
            c[3] = 'D';

            while (true)
            {
                // char c = '\0';

                // p_usart2_comm->read(std::span { &c, 1u });
                if (0x1u == flag)
                {
                    flag = 0x0u;

                    usart_async->transmit_start();
                }
            }
        }
        else
        {
            while (true)
            {
                gpio::port<gpio::A, api::traits::sync>()->toggle(gpio::A::_5);
                std::this_thread::sleep_for(1s);
            }
        }
    }

    while (true) continue;
}