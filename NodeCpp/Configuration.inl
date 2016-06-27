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

#ifndef NODECPP_CONFIGURATION_INL_
#define NODECPP_CONFIGURATION_INL_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <stdexcept>
#include <sstream>
#include <NodeCpp/Platform.h>
#include <NodeCpp/Configuration.h>

namespace NodeCpp
{
    inline const Configuration::Any* Configuration::Any::get(const std::string& _key) const
    {
        ValueMap::const_iterator _iter = Map.find(_key);
        if (_iter != Map.end()) {
            return &(_iter->second);
        }
        return NULL;
    }

    inline const Configuration::Any& Configuration::operator[](const std::string& _key) const {
        const Any* _any = get(_key);
        if (_any != NULL) {
            return *_any;
        }
        std::stringstream _ss;
        _ss << "No such key \"" << _key << "\"";
        throw std::logic_error(_ss.str());
    }

    inline const Configuration::Any& Configuration::operator[](const std::string& _key) const
    {
        const Any* _any = get(_key);
        if (_any != NULL) {
            return *_any;
        }
        std::stringstream _ss;
        _ss << "No such key \"" << _key << "\"";
        throw std::logic_error(_ss.str());
    }

    inline const std::string& Configuration::errorString(void) const
    {
        return errorString_;
    }

    template<typename T> inline T _cast(const struct Configuration::Any* _Any) 
    { return static_cast<T>(atol(_Any->Value.c_str())); }

    template<> inline std::int8_t Configuration::Any::as(void) const { return _cast<std::int8_t>(this); }
    template<> inline std::uint8_t Configuration::Any::as(void) const { return _cast<std::uint8_t>(this); }
    template<> inline std::int16_t Configuration::Any::as(void) const { return _cast<std::int16_t>(this); }
    template<> inline std::uint16_t Configuration::Any::as(void) const { return _cast<std::uint16_t>(this); }
    template<> inline std::int32_t Configuration::Any::as(void) const { return _cast<std::int32_t>(this); }
    template<> inline std::uint32_t Configuration::Any::as(void) const { return _cast<std::uint32_t>(this); }
    template<> inline std::int64_t Configuration::Any::as(void) const {
#if defined(PLATFORM_WINDOWS)
        std::int64_t _value = 0;
        if (!Value_ || sscanf_s(Value_, "%I64ld", &_value) == -1) {
            return 0;
        }
        return _value;
#else
#error
#endif
    }
    template<> inline std::uint64_t Configuration::Any::as(void) const {
#if defined(PLATFORM_WINDOWS)
        std::int64_t _value = 0;
        if (!Value_ || sscanf_s(Value_, "%I64lu", &_value) == -1) {
            return 0;
        }
        return _value;
#else
#error
#endif
    }
    template<> inline double Configuration::Any::as(void) const { return _cast<double>(this); }
    template<> inline std::string Configuration::Any::as(void) const { return Value; }
    template<> inline bool Configuration::Any::as(void) const {
        return Value.empty() ? false : (_cast<std::int8_t>(this) != 0);
    }
}

#endif // NODECPP_CONFIGURATION_INL_
