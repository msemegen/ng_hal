#pragma once

//
#include <hal/api.hpp>
#include <soc/macros.hpp>

// clang-format off
#include DECORATE_INCLUDE_PATH(soc/XMCU_SOC_VENDOR/XMCU_SOC_ARCH/stdglue.hpp)
// clang-format on

namespace hal {
using stdglue = soc::XMCU_SOC_VENDOR::XMCU_SOC_ARCH::stdglue;

} // namespace hal