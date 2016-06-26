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

#include "NodeCpp/OS/String.h"

namespace NodeCpp_OS
{
    int snprintf(char *_dest, int _size, const char *_format, ...)
    {
        int _rc = -1;
        std::va_list _args;
        va_start(_args, _format);
        _rc = NodeCpp_OS::vsnprintf(_dest, _size, _format, _args);
        va_end(_args);
        return _rc;
    }
}