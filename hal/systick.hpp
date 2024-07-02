#pragma once

//
#include <soc/macros.hpp>

// clang-format off
#include DECORATE_INCLUDE_PATH(soc/XMCU_SOC_VENDOR/XMCU_SOC_ARCH/systick.hpp)
// clang-format on

namespace hal {
using systick = soc::XMCU_SOC_VENDOR::XMCU_SOC_ARCH::systick;

} // namespace hal