#pragma once

// std
#include <cstdint>

namespace soc::st::arm::m0::u0::rm0503::clocks::details {
constexpr inline static std::uint32_t shift_lut[] = { 1u, 2u, 4u, 8u, 16u, 32u, 64u, 128u, 512u };
}