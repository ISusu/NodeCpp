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

#ifndef NODECPP_EVENT_H_
#define NODECPP_EVENT_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <NodeCpp/Macros.h>
#include <NodeCpp/Platform.h>
#if defined(PLATFORM_WINDOWS)
#include <NodeCpp/Event_WIN32.h>
#elif defined(PLATFORM_LINUX)
#include <NodeCpp/Event_POSIX.h>
#endif

namespace NodeCpp
{
    class Event : private EventImpl
    {
    public:
        Event(bool _autoReset = true, bool _initState = false)
            : EventImpl(_autoReset, _initState) {}
        ~Event(void) {}

        void set(void) { setImpl(); }
        void reset(void) { resetImpl(); }
        void wait(void) { waitImpl(); }
        void wait(long _milliseconds) { waitImpl(_milliseconds); }

    private:
        DISALLOW_COPY_AND_ASSIGN(Event);
    };
}

#endif // NODECPP_EVENT_H_
