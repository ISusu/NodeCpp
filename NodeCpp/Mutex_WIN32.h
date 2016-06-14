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

#ifndef NODECPP_MUTEX_WIN32_H_
#define NODECPP_MUTEX_WIN32_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace NodeCpp
{
    class MutexImpl
    {
    public:
        MutexImpl(void);
        ~MutexImpl(void);

        void lockImpl(void) { EnterCriticalSection(&cs_); }
        bool tryLockImpl(void) { return TryEnterCriticalSection(&cs_) != FALSE; }
        void unlockImpl(void) { LeaveCriticalSection(&cs_); }

    private:
        CRITICAL_SECTION cs_;
    };
}

#endif // NODECPP_MUTEX_WIN32_H_
