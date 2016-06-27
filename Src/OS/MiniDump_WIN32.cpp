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

#include "NodeCpp/OS/MiniDump.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <DbgHelp.h>
#include <strsafe.h>

LPTOP_LEVEL_EXCEPTION_FILTER _stPrevExceptionFilter = NULL;

LONG WINAPI _UnhandledExceptionFilter(struct _EXCEPTION_POINTERS* _expPointer)
{
    TCHAR _dumpPath[MAX_PATH] = {0, };
    SYSTEMTIME _sysTime;

    ::GetLocalTime(&_sysTime);
    ::StringCchPrintf(_dumpPath, MAX_PATH, TEXT("%d-%d-%d %d_%d_%d.dmp"),
        _sysTime.wYear,
        _sysTime.wMonth,
        _sysTime.wDay,
        _sysTime.wHour,
        _sysTime.wMinute,
        _sysTime.wSecond);

    HANDLE _hFile = ::CreateFile(_dumpPath, GENERIC_WRITE,
        FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (_hFile != INVALID_HANDLE_VALUE)
    {
        _MINIDUMP_EXCEPTION_INFORMATION _exInfo;
        _exInfo.ThreadId = GetCurrentThreadId();
        _exInfo.ExceptionPointers = _expPointer;
        _exInfo.ClientPointers = NULL;

        if (MiniDumpWriteDump(GetCurrentProcess(),
            GetCurrentProcessId(),
            _hFile,
            MiniDumpWithFullMemory,
            &_exInfo,
            NULL,
            NULL)) {
                ::CloseHandle(_hFile);
                return EXCEPTION_EXECUTE_HANDLER;
        }
        ::CloseHandle(_hFile);
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

namespace NodeCpp_OS
{
    void MiniDump::begin(void)
    {
        ::SetErrorMode(SEM_FAILCRITICALERRORS);
        _stPrevExceptionFilter = ::SetUnhandledExceptionFilter(_UnhandledExceptionFilter);
    }

    void MiniDump::end(void)
    {
        ::SetUnhandledExceptionFilter(_stPrevExceptionFilter);
    }
}