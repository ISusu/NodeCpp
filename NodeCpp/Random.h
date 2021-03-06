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

#ifndef NODECPP_RANDOM_H_
#define NODECPP_RANDOM_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cstdint>
#include <NodeCpp/Macros.h>

namespace NodeCpp
{
    class Random
    {
    public:
        Random(void);
        ~Random(void);

        void init(std::uint32_t);
        std::uint32_t rand32(void);

    private:
        std::uint32_t seed_;
        DISALLOW_COPY_AND_ASSIGN(Random);
    };
}

#endif // NODECPP_RANDOM_H_
