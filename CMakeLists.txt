cmake_minimum_required(VERSION 2.8.9)
project(opengl)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_BUILD_TYPE Debug)

link_directories(/usr/local/lib)
#Bring the headers, such as Student.h into the project
include_directories(include)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

find_package(PkgConfig REQUIRED)

find_package(OpenGL REQUIRED)
FIND_PACKAGE(SOIL REQUIRED)

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    message(STATUS "Glew found")
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${SOIL_INCLUDE_PATH})

add_executable(opengl ${SOURCES})

target_link_libraries(opengl ${GLFW_LIBRARIES})
target_link_libraries(opengl ${GLFW_STATIC_LIBRARIES})
target_link_libraries(opengl ${OPENGL_glu_LIBRARY})
target_include_directories(opengl PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(opengl ${OPENGL_gl_LIBRARY})
target_link_libraries(opengl ${SOIL_LIBRARY})