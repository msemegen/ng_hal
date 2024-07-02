#pragma once

// std
#include <cstdint>

// soc
#include <soc/non_constructible.hpp>

namespace soc::st::arm {
struct api : private soc::non_constructible
{
    template<typename Type_a> static constexpr auto interface() = delete;

    enum class traits
    {
        sync  = 0x1u,
        async = 0x2u
    };
};
} // namespace soc::st::arm
