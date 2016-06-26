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

#ifndef NODECPP_BYTECONVERTER_H_
#define NODECPP_BYTECONVERTER_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <NodeCpp/Platform.h>

namespace NodeCpp{
    namespace ByteConverter {

        template<std::size_t T>
        inline void convert(char* _v)
        {
            std::swap(*_v, *(_v + T - 1));
            convert < T - 2 >(_v + 1);
        }

        template<> inline void convert<0>(char*) {}
        template<> inline void convert<1>(char*) {}

        template<typename T>
        inline void apply(T* _v)
        {
            convert<sizeof(T)>((char*)(_v));
        }


#if defined(ENDIAN_BIG)
        template<typename T> inline void endianConvert(T& _v) { apply<T>(&_v); }
        template<typename T> inline void endianConvertReverse(T&) { }
#else
        template<typename T> inline void endianConvert(T&) { }
        template<typename T> inline void endianConvertReverse(T& _v) { Apply<T>(&_v); }
#endif

        template<typename T> void endianConvert(T*);
        template<typename T> void endianConvertReverse(T*);
        inline void endianConvert(std::uint8_t&) { }
        inline void endianConvert(std::int8_t&)  { }
        inline void endianConvertReverse(std::uint8_t&) { }
        inline void endianConvertReverse(std::int8_t&) { }
    }
}

#endif // NODECPP_BYTECONVERTER_H_
