cmake_minimum_required(VERSION 4.1)
project(numericore)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
if(GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

add_executable(numericore src/main.cpp)
target_include_directories(numericore PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/headers")
target_link_libraries(numericore PRIVATE fmt::fmt OpenGL::GL GLEW::GLEW glfw)
