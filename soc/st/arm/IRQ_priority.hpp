#pragma once

// std
#include <cstdint>

namespace soc::st::arm {
struct IRQ_priority
{
    std::uint32_t preempt_priority = 0;
    std::uint32_t sub_priority     = 0;
};
} // namespace soc::st::arm