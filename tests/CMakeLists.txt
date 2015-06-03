cmake_minimum_required(VERSION 2.8.4)
project(Tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(STATIC_RUNTIM_LIBRARY "Static runtime library" ON)
option(UNICODE "Character set is UNICODE" ON)

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

if(UNICODE)
    add_definitions(-D_UNICODE -DUNICODE)
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

if(WIN32 AND MSVC AND NOT BUILD_SHARED_LIBS)
    include(cmake/FindStaticOpenSSL.cmake)
else()
    find_package(OpenSSL)
endif()
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(Pugixml REQUIRED)
include_directories(${Pugixml_INCLUDE_DIRS})

find_package(Curl REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

target_link_libraries(${PROJECT_NAME} Pugixml ${OPENSSL_LIBRARIES} ${CURL_LIBRARY} Webdavclient)
