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

#ifndef NODECPP_LOCKEDQUEUE_H_
#define NODECPP_LOCKEDQUEUE_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <deque>
#include <NodeCpp/Macros.h>
#include <NodeCpp/LockGuard.h>

namespace NodeCpp
{
    template<typename T, class LockType, class StorageType = std::deque<T> >
    class LockedQueue
    {
    public:
        LockedQueue(void) : lock_(), storage_() {}
        ~LockedQueue(void) {}

        void add(const T& _v)
        {
            LockGuard<LockType> _guard(lock_);
            storage_.push_back(_v);
        }

        bool next(T& _v)
        {
            LockGuard<LockType> _guard(lock_);
            if (storage_.empty()) {
                return false;
            }
            _v = storage_.front();
            storage_.pop_front();
            return true;
        }

        template<class Checker>
        bool next(T& _v, Checker& _checker)
        {
            LockGuard<LockType> _guard(lock_);
            if (storage_.empty()) {
                return false;
            }
            _v = storage_.front();
            if (!_checker.process(_v)) {
                return false;
            }
            storage_.pop_front();
            return true;
        }

    private:
        LockType lock_;
        StorageType storage_;
        DISALLOW_COPY_AND_ASSIGN(LockedQueue);
    };
}

#endif // NODECPP_LOCKEDQUEUE_H_
