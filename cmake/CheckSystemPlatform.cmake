include(CheckTypeSize)
include(TestBigEndian)

macro(CHECK_SYSTEM_PLATFORM _PLATFORM _ARCH _ENDIAN)
    message(STATUS "Operation System is ${CMAKE_SYSTEM}")
    
    # 平台检测
    if (CMAKE_SYSTEM_NAME MATCHES "Windows")
        set(${_PLATFORM} PLATFORM_WINDOWS)
        set(PLATFORM_WINDOWS TRUE)
    elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
        set(${_PLATFORM} PLATFORM_LINUX)
        set(PLATFORM_LINUX TRUE)
    elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
        set(${_PLATFORM} PLATFORM_APPLE)
        set(PLATFORM_APPLE TRUE)
    endif()
    
    # 架构检测
    CHECK_TYPE_SIZE("void*" POINTER_SIZE)
    if (${POINTER_SIZE} MATCHES 8)
        set(${_ARCH} ARCH_X64)
        set(ARCH_X64 TRUE)
    else()
        set(${_ARCH} ARCH_X86)
        set(ARCH_X86 TRUE)
    endif()
    
    # 大小端检测
    TEST_BIG_ENDIAN(BIG_ENDIAN)
    if (${BIG_ENDIAN})
        set(${_ENDIAN} ENDIAN_BIG)
    else()
        set(${_ENDIAN} ENDIAN_LITTLE)
    endif()
endmacro()
