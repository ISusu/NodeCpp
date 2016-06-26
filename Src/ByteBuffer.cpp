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

#include "NodeCpp/ByteBuffer.h"
#include <cstring>
#include "NodeCpp/OS/String.h"

namespace NodeCpp
{
    ByteBufferException::ByteBufferException(bool _add, std::size_t _pos, 
        std::size_t _opSize, std::size_t _bufSize)
    {
        NodeCpp_OS::snprintf(message_, EXCEP_BUFF_SIZE, 
            "Try %s %d bytes at pos(%d), buffer size(%d)", 
            _add ? "add" : "read", _opSize, _pos, _bufSize);
    }

    ByteBufferException::ByteBufferException(const ByteBufferException& _excep)
    {
        memcpy(&message_[0], &_excep.message_[0], EXCEP_BUFF_SIZE);
    }

    ByteBufferException::~ByteBufferException(void)
    {

    }

    ByteBuffer::ByteBuffer(void)
        : rpos_(0)
        , wpos_(0)
        , storage_()
    {
        storage_.reserve(DEFAULT_SIZE);
    }

    ByteBuffer::ByteBuffer(size_type _res)
        : rpos_(0)
        , wpos_(0)
        , storage_()
    {
        storage_.reserve(_res);
    }

    ByteBuffer::ByteBuffer(const ByteBuffer& _buf)
        : rpos_(0)
        , wpos_(0)
        , storage_(_buf.storage_)
    {

    }

    ByteBuffer::~ByteBuffer(void)
    {

    }
}