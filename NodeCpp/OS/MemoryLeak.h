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

#ifndef NODECPP_OS_MEMORYLEAK_H_
#define NODECPP_OS_MEMORYLEAK_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <NodeCpp/Macros.h>
#include <NodeCpp/Platform.h>

#if defined(PLATFORM_WINDOWS)

#ifdef _MSC_VER
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifndef _CONSOLE
#include <cstdlib>
#endif // _CONSOLE

namespace NodeCpp_OS
{
    class MemoryLeak
    {
    public:
        MemoryLeak(void)
        {
#if 1
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
            _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
            _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
            _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
            _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
            _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
            _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

#define DEBUG_NORMAL_BLOCK new (_NORMAL_BLOCK, __FILE__, __LINE__)
#ifdef new
#undef new
#endif // new
#define new DEBUG_NORMAL_BLOCK
#else
            _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
            _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
            _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
#endif // 1

#ifdef malloc
#undef malloc
#define malloc(s) (_malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__))
#endif // malloc
        }

    private:
        DISALLOW_COPY_AND_ASSIGN(MemoryLeak);
    };
}

static NodeCpp_OS::MemoryLeak _stMemoryLeak;

#endif // _DEBUG
#endif // _MSC_VER

#endif // defined(PLATFORM_WINDOWS)

#endif // NODECPP_OS_MEMORYLEAK_H_
