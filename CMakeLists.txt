cmake_minimum_required(VERSION 4.1)
project(numericore)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt CONFIG REQUIRED)

add_executable(numericore src/main.cpp)
target_link_libraries(numericore PRIVATE fmt::fmt)
