#pragma once

// xmcu
#include <xmcu/non_constructible.hpp>

namespace xmcu {
template<typename Object_t> class Scoped_guard : private non_constructible
{
};
} // namespace xmcu