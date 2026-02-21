cmake_minimum_required(VERSION 4.1)
project(numericore)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
if(GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/headers/*.h"
)

file(GLOB_RECURSE RESOURCE_FILES
        "${CMAKE_SOURCE_DIR}/res/*"
)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_BINARY_DIR}/res
)

add_executable(numericore ${SOURCES} ${HEADERS}
        headers/graphics/Camera.h
        headers/graphics/models/Mesh.h
        src/graphics/models/Mesh.cpp
        headers/graphics/models/Model.h
        src/graphics/models/Model.cpp
        headers/util/InputHandler.h)

target_include_directories(numericore PRIVATE
        "${CMAKE_SOURCE_DIR}/headers"
)

add_dependencies(numericore copy_resources)

target_link_libraries(numericore PRIVATE fmt::fmt OpenGL::GL GLEW::GLEW glfw glm::glm assimp::assimp)
