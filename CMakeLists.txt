cmake_minimum_required(VERSION 3.16)
project(utf8_parser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -std=c++2a")

file(GLOB SOURCES "*.cpp")
add_executable(utf8_parser ${SOURCES})