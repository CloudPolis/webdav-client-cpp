cmake_minimum_required(VERSION 2.8.4)
project(Tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)

if(STATIC_RUNTIM_LIBRARY)
    set(CompilerFlags
                CMAKE_CXX_FLAGS
                CMAKE_CXX_FLAGS_DEBUG
                CMAKE_CXX_FLAGS_RELEASE
                CMAKE_C_FLAGS
                CMAKE_C_FLAGS_DEBUG
                CMAKE_C_FLAGS_RELEASE)
    foreach(CompilerFlag ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
endif()

set(${PROJECT_NAME}_sources ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/source/check.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/source/clean.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/source/list.cpp
							${CMAKE_CURRENT_SOURCE_DIR}/source/stdafx.h
                            ${CMAKE_CURRENT_SOURCE_DIR}/source/config.hpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/source/catch.hpp)

find_package(Webdavclient REQUIRED)
include_directories(${Webdavclient_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

target_link_libraries(${PROJECT_NAME} Webdavclient)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${PROJECT_NAME} -s -r compact WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/..)
