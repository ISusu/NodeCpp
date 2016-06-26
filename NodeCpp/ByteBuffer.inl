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

#ifndef NODECPP_BYTEBUFFER_INL_
#define NODECPP_BYTEBUFFER_INL_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <NodeCpp/ByteBuffer.h>
#include <cassert>
#include <cstring>

namespace NodeCpp
{
    inline const char* ByteBufferException::what(void) const throw()
    {
        return &message_[0];
    }

    inline ByteBuffer::size_type ByteBuffer::size(void) const
    {
        return storage_.size();
    }

    inline void ByteBuffer::resize(size_type _newres)
    {
        storage_.resize(_newres);
    }

    inline ByteBuffer::size_type ByteBuffer::rpos(void) const
    {
        return rpos_;
    }

    inline ByteBuffer::size_type ByteBuffer::wpos(void) const
    {
        return wpos_;
    }

    inline void ByteBuffer::rpos(ByteBuffer::size_type _pos)
    {
        rpos_ = _pos;
    }

    inline void ByteBuffer::wpos(ByteBuffer::size_type _pos)
    {
        wpos_ = _pos;
    }

    inline const std::uint8_t* ByteBuffer::contents(void) const
    {
        assert(storage_.size() > 0);
        return &storage_[0];
    }

    inline std::uint8_t* ByteBuffer::contents(ByteBuffer::size_type _pos)
    {
        assert(storage_.size() > 0 && _pos >= 0 && _pos < storage_.size());
        return &storage_[_pos];
    }

    inline ByteBuffer::Self& ByteBuffer::operator>>(std::uint8_t& _v)
    {
        _v = read<std::uint8_t>();
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator>>(std::int8_t& _v)
    {
        _v = read<std::int8_t>();
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator>>(std::uint16_t& _v)
    {
        _v = read<std::uint16_t>();
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator>>(std::int16_t& _v)
    {
        _v = read<std::int16_t>();
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator>>(std::uint32_t& _v)
    {
        _v = read<std::uint32_t>();
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator>>(std::int32_t& _v)
    {
        _v = read<std::int32_t>();
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator>>(std::uint64_t& _v)
    {
        _v = read<std::uint64_t>();
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator>>(std::int64_t& _v)
    {
        _v = read<std::int64_t>();
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator>>(std::string& _v)
    {
        _v.clear();
        while (rpos_ < size())
        {
            char _c = read<char>();
            if (_c == '\0')
            {
                break;
            }
            _v += _c;
        }
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator>>(float& _v)
    {
        _v = read<float>();
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator>>(double& _v)
    {
        _v = read<double>();
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator<<(std::uint8_t _v)
    {
        append<std::uint8_t>(_v);
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator<<(std::int8_t _v)
    {
        append<std::int8_t>(_v);
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator<<(std::uint16_t _v)
    {
        append<std::uint16_t>(_v);
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator<<(std::int16_t _v)
    {
        append<std::int16_t>(_v);
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator<<(std::uint32_t _v)
    {
        append<std::uint32_t>(_v);
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator<<(std::int32_t _v)
    {
        append<std::int32_t>(_v);
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator<<(const std::uint64_t& _v)
    {
        append<std::uint64_t>(_v);
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator<<(const std::int64_t& _v)
    {
        append<std::int64_t>(_v);
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator<<(const std::string& _v)
    {
        append((const std::uint8_t*)_v.c_str(), _v.size());
        append<std::uint8_t>(0);
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator<<(const float& _v)
    {
        append<float>(_v);
        return *this;
    }

    inline ByteBuffer::Self& ByteBuffer::operator<<(const double& _v)
    {
        append<double>(_v);
        return *this;
    }

    inline void ByteBuffer::append(const std::uint8_t* _ptr, ByteBuffer::size_type _size)
    {
        if (_size == 0) {
            return;
        }

        if ((_size + wpos_) > MAX_SIZE) {
            throw ByteBufferException(true, wpos_, _size, size());
        }

        if (size() < (_size + wpos_)) {
            storage_.resize(_size + wpos_);
        }

        memcpy(&storage_[wpos_], _ptr, _size);
        wpos_ += _size;
    }

    inline void ByteBuffer::append(const ByteBuffer& _buf)
    {
        append(_buf.contents(), _buf.size());
    }

    inline void ByteBuffer::read(std::uint8_t* _ptr, ByteBuffer::size_type _size)
    {
        if ((rpos_ + _size) > size())
        {
            throw ByteBufferException(false, rpos_, _size, size());
        }
        memcpy(_ptr, &storage_[rpos_], _size);
        rpos_ += _size;
    }

    template<typename T>
    inline T ByteBuffer::read(void)
    {
        T _ret = read<T>(rpos_);
        rpos_ += sizeof(T);
        return _ret;
    }

    inline void ByteBuffer::put(ByteBuffer::size_type _pos, const std::uint8_t* _ptr, ByteBuffer::size_type _size)
    {
        if ((_pos + _size) > size()) {
            throw ByteBufferException(true, _pos, size(), _size);
        }
        memcpy(&storage_[_pos], _ptr, _size);
    }

    template<typename T>
    inline void ByteBuffer::put(ByteBuffer::size_type _pos, const T& _v)
    {
        put(_pos, (const std::uint8_t*)&_v, sizeof(T));
    }

    template<typename T>
    inline void ByteBuffer::append(const T& _v)
    {
        append((const std::uint8_t*)&_v, sizeof(T));
    }

    template<typename T>
    inline T ByteBuffer::read(ByteBuffer::size_type _pos)
    {
        if (_pos + sizeof(T) > size()) {
            throw ByteBufferException(false, _pos, sizeof(T), size());
        }
        T _ret = *((T const*)&storage_[_pos]);
        return _ret;
    }
}

#endif // NODECPP_BYTEBUFFER_INL_
