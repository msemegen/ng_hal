#pragma once

// std
#include <cstdint>

//
#include <soc/bit_flag.hpp>

namespace soc::st::arm {
template<typename Enum_t> struct Register
{
    constexpr operator std::uint32_t() const
    {
        return this->v;
    }
    constexpr operator Enum_t() const
    {
        return static_cast<Enum_t>(this->v);
    }

    constexpr void set(Enum_t flag_a)
    {
        bit_flag::set(&(this->v), static_cast<std::uint32_t>(flag_a));
    }
    constexpr void clear(Enum_t flag_a)
    {
        bit_flag::clear(&(this->v), static_cast<std::uint32_t>(flag_a));
    }

    constexpr bool is(Enum_t flag_a) const
    {
        return bit_flag::is(this->v, static_cast<std::uint32_t>(flag_a));
    }

private:
    volatile std::uint32_t v;
};
} // namespace soc::st::arm
