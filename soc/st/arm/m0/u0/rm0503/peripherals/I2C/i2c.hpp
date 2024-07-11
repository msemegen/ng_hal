#pragma once

/*
 */

// soc
#include <soc/non_constructible.hpp>

namespace soc::st::arm::m0::u0::rm0503::peripherals {
namespace ll {
struct i2c_clock : private non_constructible
{
};

struct i2c : private non_constructible
{
};
} // namespace ll

struct i2c : private non_constructible
{
};
} // namespace soc::st::arm::m0::u0::rm0503::peripherals