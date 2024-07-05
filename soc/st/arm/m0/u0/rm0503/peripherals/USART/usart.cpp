#if XMCU_SOC_ARCH_CORE_FAMILY == m0 && XMCU_SOC_VENDOR_FAMILY == stm32u0 && XMCU_SOC_VENDOR_FAMILY_RM == rm0503

// soc
#include <soc/st/arm/m0/u0/rm0503/peripherals/USART/usart.hpp>

namespace {
constexpr std::uint32_t clock_prescaler_lut[] = { 1u, 2u, 4u, 6u, 8u, 10u, 12u, 16u, 32u, 64u, 128u, 256u };
}

namespace soc::st::arm::m0::u0::rm0503::peripherals {
void usart::Peripheral::set_descriptor(const Clock& clock_a, const Descriptor& descriptor_a)
{
    xmcu_assert(0x0 != clock_a.clk_freq_Hz);

#if defined XMCU_ASSERT_PRESENT
    constexpr std::uint32_t brr_min = 0x10u;
    constexpr std::uint32_t brr_max = 0xFFFFu;
#endif

    this->cr1 = 0x0u;
    this->cr2 = 0x0u;
    this->cr3 = 0x0u;

    this->presc = static_cast<std::uint32_t>(clock_a.prescaler);

    if (usart::Descriptor::Auto_baudrate::disable == (usart::Descriptor::Auto_baudrate::disable & descriptor_a.auto_baudrate))
    {
        const std::uint32_t baudrate = static_cast<std::uint32_t>((static_cast<std::uint64_t>(descriptor_a.auto_baudrate) >> 32u) & 0xFFFFFFFF);
        switch (descriptor_a.oversampling)
        {
            case usart::Descriptor::Oversampling::_8: {
                std::uint32_t div =
                    ((((clock_a.clk_freq_Hz / clock_prescaler_lut[static_cast<std::uint32_t>(clock_a.prescaler)]) * 2u) + (baudrate / 2u)) /
                     baudrate);
#if defined XMCU_ASSERT_PRESENT
                xmcu_assert(div >= brr_min && div <= brr_max);
#endif
                std::uint16_t brr = static_cast<std::uint16_t>(div & 0xFFF0u);
                brr |= static_cast<std::uint16_t>((div & 0xFu) >> 1u);
                this->brr = brr;
            }
            break;

            case usart::Descriptor::Oversampling::_16: {
                std::uint32_t div =
                    ((clock_a.clk_freq_Hz / clock_prescaler_lut[static_cast<std::uint32_t>(clock_a.prescaler)] + (baudrate / 2u)) /
                     baudrate);
#if defined XMCU_ASSERT_PRESENT
                xmcu_assert(div >= brr_min && div <= brr_max);
#endif
                this->brr = static_cast<std::uint16_t>(div);
            }
            break;
        }
    }

    bit_flag::set(&(this->cr1),
                  static_cast<std::uint32_t>(descriptor_a.fifo) | static_cast<std::uint32_t>(descriptor_a.oversampling) |
                      static_cast<std::uint32_t>(descriptor_a.mute) | static_cast<std::uint32_t>(descriptor_a.frame.parity) |
                      static_cast<std::uint32_t>(descriptor_a.frame.word_length));
    bit_flag::set(&(this->cr2),
                  (static_cast<std::uint32_t>(descriptor_a.mute) & 0xFF) | static_cast<std::uint32_t>(descriptor_a.auto_baudrate) |
                      static_cast<std::uint32_t>(descriptor_a.frame.stop_bits) | static_cast<std::uint32_t>(descriptor_a.frame.msb_first) |
                      static_cast<std::uint32_t>(descriptor_a.frame.inversion));
    bit_flag::set(&(this->cr3), static_cast<std::uint32_t>(descriptor_a.sampling));
}

bool usart::Peripheral::enable(Mode mode_a, std::chrono::milliseconds timeout_a)
{
    bit_flag::set(&(this->cr1), static_cast<std::uint32_t>(mode_a) | USART_CR1_UE);
    bit_flag::set(&(this->icr), USART_ICR_TCCF | USART_ICR_IDLECF);

    return wait_for::all_bits_are_set(this->isr,
                                      (usart::Mode::rx == (mode_a & usart::Mode::rx) ? USART_ISR_REACK : 0x0u) |
                                          (usart::Mode::tx == (mode_a & usart::Mode::tx) ? USART_ISR_TEACK : 0x0u),
                                      timeout_a);
}
bool usart::Peripheral::disable(std::chrono::milliseconds timeout_a)
{
    bit_flag::clear(&(this->cr1), USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);
    return wait_for::all_bits_are_cleared(this->isr, USART_ISR_REACK | USART_ISR_TEACK, timeout_a);
}
} // namespace soc::st::arm::m0::u0::rm0503::peripherals
#endif