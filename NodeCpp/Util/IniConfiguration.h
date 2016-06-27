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

#ifndef NODECPP_UTIL_INICONFIGURATION_H_
#define NODECPP_UTIL_INICONFIGURATION_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <NodeCpp/Configuration.h>

namespace NodeCpp{
    namespace Util
    {
        class IniConfiguration : public Configuration
        {
        public:
            IniConfiguration(void);
            ~IniConfiguration(void);

            virtual bool open(const std::string&);
            virtual const Configuration::Any* get(const std::string& _key) const;

        private:
            bool _parseLine(std::string&);
            Configuration::Any conf_;
            std::string secName_;
        };
    }
}

#endif // NODECPP_UTIL_INICONFIGURATION_H_
