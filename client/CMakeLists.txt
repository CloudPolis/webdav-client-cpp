cmake_minimum_required(VERSION 2.8.4)
project(webdavclient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(${PROJECT_NAME}_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/stdafx.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/callback.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/fsinfo.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/request.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/urn.cpp)

set(${PROJECT_NAME}_headers ${CMAKE_CURRENT_SOURCE_DIR}/src/stdafx.h
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/callback.hpp
                            inc/client.hpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/fsinfo.hpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/request.hpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/urn.hpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/pugiext.hpp)

include_directories(./inc/)

add_definitions(-DUSE_SSLEAY -DUSE_OPENSSL -DCURL_STATICLIB -DNOMINMAX)

add_library(webdavclient STATIC ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})