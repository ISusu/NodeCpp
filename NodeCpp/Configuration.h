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

#ifndef NODECPP_CONFIGURATION_H_
#define NODECPP_CONFIGURATION_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cstdint>
#include <cstring>
#include <string>
#include <map>
#include <NodeCpp/Macros.h>

namespace NodeCpp
{
    class Configuration
    {
    public:
        //---------------------------------------------------------------------
        struct _Any;
        typedef std::map<std::string, struct _Any>   ValueMap;

        typedef struct _Any {
            std::string Key;
            std::string Value;
            ValueMap Map;

            const struct _Any* get(const std::string& _key) const;
            const struct _Any& operator[](const std::string& _key) const;

            template<typename T>
            T as(void) const;
        }Any;

        //---------------------------------------------------------------------
        Configuration(void) : errorString_() {}
        ~Configuration(void){}

        virtual bool open(const std::string&) = 0;
        virtual const Any* get(const std::string& _key) const = 0;

        const Any& operator[](const std::string& _key) const;
        const std::string& errorString(void) const;

    protected:
        std::string errorString_;
    private:
        DISALLOW_COPY_AND_ASSIGN(Configuration);
    };
}

#include <NodeCpp/Configuration.inl>

#endif // NODECPP_CONFIGURATION_H_
