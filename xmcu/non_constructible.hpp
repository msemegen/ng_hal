#pragma once

/*
 *  Name: non_constructible.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

namespace xmcu {
class non_constructible
{
protected:
    non_constructible() = delete;
    non_constructible(const non_constructible&) = delete;
    non_constructible(non_constructible&&) = delete;

    non_constructible& operator=(const non_constructible&) = delete;
    non_constructible& operator=(non_constructible&&) = delete;
};
} // namespace xmcu