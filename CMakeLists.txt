#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.6)
project(NodeCpp)

#------------------------------------------------------------------------------
# 查找依赖
include(cmake/Dependencies.cmake)

#------------------------------------------------------------------------------
# 工程设置
if (UNIX)
  add_definitions(-Wall)
  if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
  else ()
    add_definitions(-std=stdc++11)
  endif()
endif()
add_definitions(-D_BUILD)

#------------------------------------------------------------------------------
# 配置工程
include(cmake/CheckSystemPlatform.cmake)
CHECK_SYSTEM_PLATFORM(SYSTEM_PLATFORM SYSTEM_ARCH SYSTEM_ENDIAN)
configure_file(Config.h.in ${PROJECT_SOURCE_DIR}/NodeCpp/Config.h)

#------------------------------------------------------------------------------
# 设置头文件路径
include_directories(
  "${PROJECT_SOURCE_DIR}"
)

#------------------------------------------------------------------------------
# 工程源文件
if (WIN32)
  set(SRC_PLAT "WIN32")
elseif (UNIX)
  set(SRC_PLAT "POSIX")
endif()

set(NodeCpp_OS_SRC
  NodeCpp/OS/String.h
  
  Src/OS/String.cpp
  Src/OS/String_${SRC_PLAT}.cpp
)

set(NodeCpp_Base_SRC
  NodeCpp/Macros.h
  NodeCpp/Platform.h
  NodeCpp/ByteConverter.h
  NodeCpp/ByteBuffer.h
  NodeCpp/ByteBuffer.inl
  NodeCpp/Configuration.h
  NodeCpp/Configuration.inl
  
  Src/ByteBuffer.cpp
)

if (WIN32)
  source_group("OS" FILES ${NodeCpp_OS_SRC})
  source_group("Base" FILES ${NodeCpp_Base_SRC})
endif()

#------------------------------------------------------------------------------
# 生成目标
add_library(NodeCpp STATIC
  ${NodeCpp_OS_SRC}
  ${NodeCpp_Base_SRC}
)