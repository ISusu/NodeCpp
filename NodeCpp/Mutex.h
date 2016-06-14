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

#ifndef NODECPP_MUTEX_H_
#define NODECPP_MUTEX_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <NodeCpp/Macros.h>
#include <NodeCpp/Platform.h>
#if defined(PLATFORM_WINDOWS)
#include <NodeCpp/Mutex_WIN32.h>
#else
#error
#endif

namespace NodeCpp
{
    class NullMutex
    {
    public:
        NullMutex(void) {}
        ~NullMutex(void) {}

        void lock(void) {}
        void unlock(void) {}
        void tryLock(void) {}

    private:
        DISALLOW_COPY_AND_ASSIGN(NullMutex);
    };

    class Mutex : private MutexImpl
    {
    public:
        Mutex(void) {}
        ~Mutex(void) {}

        void lock(void) { lockImpl(); }
        void unlock(void) { unlockImpl(); }
        void tryLock(void) { tryLockImpl(); }

    private:
        DISALLOW_COPY_AND_ASSIGN(Mutex);
    };
}

#endif // NODECPP_MUTEX_H_
