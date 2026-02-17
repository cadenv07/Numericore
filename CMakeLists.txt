cmake_minimum_required(VERSION 4.1)
project(numericore)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt CONFIG REQUIRED)
find_package(GLEW REQUIRED)
if(GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

add_executable(numericore src/main.cpp)
target_link_libraries(numericore PRIVATE fmt::fmt)
