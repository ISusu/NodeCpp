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

#ifndef NODECPP_EVENT_WIN32_H_
#define NODECPP_EVENT_WIN32_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <stdexcept>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace NodeCpp
{
    class EventImpl
    {
    public:
        EventImpl(bool _autoReset, bool _initState);
        ~EventImpl(void);

        void setImpl(void)
        {
            if (!SetEvent(event_)) {
                throw std::runtime_error("Failed set event.");
            }
        }

        void resetImpl(void)
        {
            if (!ResetEvent(event_)) {
                throw std::runtime_error("Failed reset event.");
            }
        }

        void waitImpl(void)
        {
            if (WaitForSingleObject(event_, INFINITE) == WAIT_FAILED) {
                throw std::runtime_error("Failed wait event.");
            }
        }

        void waitImpl(long _milliseconds)
        {
            if (WaitForSingleObject(event_, (DWORD)_milliseconds) == WAIT_FAILED) {
                throw std::runtime_error("Failed wait event.");
            }
        }

    private:
        HANDLE event_;
    };
}

#endif // NODECPP_EVENT_WIN32_H_
