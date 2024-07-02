#pragma once

namespace soc::st::arm::m0::u0::rm0503::clocks {
namespace ll {
struct pclk
{
};
} // namespace ll

struct pclk
{
    static std::uint32_t get_frequency_Hz()
    {
        return 0x0u;
    }
};
} // namespace soc::st::arm::m0::u0::rm0503::clocks