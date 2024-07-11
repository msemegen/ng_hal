#pragma once

// soc
#include <soc/non_constructible.hpp>

namespace soc::st::arm::m0::u0::rm0503::oscillators {
namespace ll {
struct hsi48
{
    // ?
};
} // namespace ll

struct hsi48 : private non_constructible
{
};
} // namespace soc::st::arm::m0::u0::rm0503::oscillators