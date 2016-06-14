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

#ifndef NODECPP_BYTEBUFFER_H_
#define NODECPP_BYTEBUFFER_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <exception>

namespace NodeCpp
{
    class ByteBufferException : public std::exception
    {
    public:
        ByteBufferException(bool _add, std::size_t _pos, 
            std::size_t _opSize, std::size_t _bufSize);
        ByteBufferException(const ByteBufferException& _excep);
        ~ByteBufferException(void);
        const char* what(void) const throw();

    private:
        const static std::size_t EXCEP_BUFF_SIZE = 128;
        char message_[EXCEP_BUFF_SIZE];
    };

    class ByteBuffer
    {
    public:
        typedef std::vector<std::uint8_t>   Storage;
        typedef Storage::size_type          size_type;
        typedef ByteBuffer                  Self;

        const static size_type DEFAULT_SIZE = 0x1000;
        const static size_type MAX_SIZE = 0x1000000;

        ByteBuffer(void);
        ByteBuffer(size_type);
        ByteBuffer(const ByteBuffer&);
        ~ByteBuffer(void);

        size_type size(void) const;
        void resize(size_type);

        const std::uint8_t* rptr(size_type) const;
        std::uint8_t* wptr(size_type);

        size_type rpos(void) const;
        void rpos(size_type);

        size_type wpos(void) const;
        void wpos(size_type);

        void append(const std::uint8_t*, size_type);
        void append(const ByteBuffer&);

        void read(std::uint8_t*, size_type);
        template<typename T> T read(void);

        void put(size_type, const std::uint8_t*, size_type);

        Self& operator>>(std::uint8_t&);
        Self& operator>>(std::int8_t&);
        Self& operator>>(std::uint16_t&);
        Self& operator>>(std::int16_t&);
        Self& operator>>(std::uint32_t&);
        Self& operator>>(std::int32_t&);
        Self& operator>>(std::uint64_t&);
        Self& operator>>(std::int64_t&);
        Self& operator>>(std::string&);
        Self& operator>>(float&);
        Self& operator>>(double&);

        Self& operator<<(std::uint8_t);
        Self& operator<<(std::int8_t);
        Self& operator<<(std::uint16_t);
        Self& operator<<(std::int16_t);
        Self& operator<<(std::uint32_t);
        Self& operator<<(std::int32_t);
        Self& operator<<(const std::uint64_t&);
        Self& operator<<(const std::int64_t&);
        Self& operator<<(const std::string&);
        Self& operator<<(const float&);
        Self& operator<<(const double&);

    private:
        template<typename T> void _append(const T&);
        template<typename T> T _read(size_type);
        template<typename T> void _put(size_type, T&);

        size_type rpos_;
        size_type wpos_;
        Storage storage_;
    };
}

#include <NodeCpp/ByteBuffer.inl>

#endif // NODECPP_BYTEBUFFER_H_
