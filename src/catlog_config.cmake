cmake_minimum_required(VERSION 3.22)
project(catlog)


if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "current platform: Linux ")
    file(GLOB_RECURSE CATLOG_SRC catlog.c catlog_port_linux.c)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "current platform: Windows")
    file(GLOB_RECURSE CATLOG_SRC catlog.c catlog_port_win32.c)
elseif (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    message(STATUS "current platform: FreeBSD")
    file(GLOB_RECURSE CATLOG_SRC catlog.c catlog_port_linux.c)
else ()
    file(GLOB_RECURSE CATLOG_SRC catlog.c catlog_port_rtos.c)
endif (CMAKE_SYSTEM_NAME MATCHES "Linux")

set(CATLOG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
message("SRC:${CATLOG_SRC}")




