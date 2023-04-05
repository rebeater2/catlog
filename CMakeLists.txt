cmake_minimum_required(VERSION 3.22)
project(catlog)
set(CMAKE_CXX_STANDARD 14)

include(src/catlog_config.cmake)
include_directories(src)

add_compile_options(-Ofast)
add_executable(test_base test/test_base.c ${CATLOG_SRC})
add_executable(test_mult_thread test/test_mult_thread.c ${CATLOG_SRC})

target_link_libraries(test_mult_thread pthread)
