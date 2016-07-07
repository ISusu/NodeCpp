/******************************************************************************
 * Copyright (C) 671643387@qq.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *****************************************************************************/

#include "NodeCpp/Random.h"
#include <ctime>

namespace NodeCpp
{
    Random::Random(void)
        : seed_(std::uint32_t(time(NULL)))
    {

    }

    Random::~Random(void)
    {

    }

    void Random::init(std::uint32_t _seed)
    {
        seed_ = _seed;
    }

    std::uint32_t Random::rand32(void)
    {
        std::uint32_t _next = seed_;
        std::uint32_t _ret;
        _next *= 1103515245; _next += 12345; _ret = (_next / 65536) % 2048;
        _next *= 1103515245; _next += 12345; _ret <<= 10; _ret ^= (_next / 65536) % 1024;
        _next *= 1103515245; _next += 12345; _ret <<= 10; _ret ^= (_next / 65536) % 1024;
        seed_ = _next;
        return _ret;
    }
}