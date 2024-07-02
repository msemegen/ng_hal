#pragma once

/*
 */

// std
#include <cstdint>
#include <limits>
#include <type_traits>

// soc
#include <soc/Non_constructible.hpp>

namespace soc {
struct various : private non_constructible
{
    template<typename Type_t> constexpr static Type_t get_enum_incorrect_value()
    {
        static_assert(true == std::is_enum<Type_t>::value);
        return static_cast<Type_t>(std::numeric_limits<std::underlying_type_t<Type_t>>::max());
    }
    template<typename Type_t, std::size_t count> constexpr static std::size_t countof(Type_t (&arr)[count])
    {
        return std::extent<Type_t[count]>::value;
    }
    template<typename t_enum_type>
    constexpr static std::underlying_type_t<t_enum_type> to_underlying(t_enum_type a_enum)
    {
        return static_cast<std::underlying_type_t<t_enum_type>>(a_enum);
    }
};
} // namespace soc
