cmake_minimum_required(VERSION 2.8.4)
project(webdavclient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(./inc/)

set(${PROJECT_NAME}_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/stdafx.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/callback.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/fsinfo.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/header.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/request.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/urn.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/stdafx.h
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/callback.hpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/fsinfo.hpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/header.hpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/request.hpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/urn.hpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/pugiext.hpp)

set(${PROJECT_NAME}_headers ${CMAKE_CURRENT_SOURCE_DIR}/inc/client.hpp)

add_definitions(-DUSE_SSLEAY -DUSE_OPENSSL -DCURL_STATICLIB -DNOMINMAX)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

install(FILES ${${PROJECT_NAME}_headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_subdirectory(tests)