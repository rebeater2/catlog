cmake_minimum_required(VERSION 3.22)
project(catlog)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_base test_base.c src/catlog.c src/catlog_port.c)
add_executable(test_mult_thread test_mult_thread.c src/catlog.c src/catlog_port.c)

target_link_libraries(test_mult_thread pthread)
