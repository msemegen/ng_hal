#pragma once

/*
 *	Name: Non_copyable.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

namespace xmcu {
class non_copyable
{
public:
    non_copyable() = default;
    non_copyable(non_copyable&&) = default;
    non_copyable& operator=(non_copyable&&) = default;

protected:
    non_copyable(const non_copyable&) = delete;
    non_copyable& operator=(const non_copyable&) = delete;
};
} // namespace xmcu