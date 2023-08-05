#Cmake version.
cmake_minimum_required(VERSION 3.10.2)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(ExternalProject)
set(CMAKE_EXE_LINKER_FLAGS "-no-pie")

# Project
project(H2S VERSION 1.0.0 LANGUAGES C DESCRIPTION "Http2 Simple Server")
option(BUILD_DEBUG "Build Debug" ON)
if(BUILD_DEBUG)
    add_definitions(-DDEBUG)
endif(BUILD_DEBUG)


# libiv
ExternalProject_Add(libuv
    GIT_REPOSITORY https://github.com/libuv/libuv.git
    GIT_TAG v1.46.0
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_SOURCE_DIR}/lib/local)

include_directories(
    ${CMAKE_SOURCE_DIR}/lib/local/include)

link_directories(
    ${CMAKE_SOURCE_DIR}/lib/local/lib/
    ${CMAKE_SOURCE_DIR}/lib/local/lib64/)

file(GLOB SRC
    src/*.c src/log/*.c)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})
target_link_libraries(${CMAKE_PROJECT_NAME} uv) 
add_custom_target(run ${CMAKE_PROJECT_NAME}
    DEPENDS ${SAMPLE}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
