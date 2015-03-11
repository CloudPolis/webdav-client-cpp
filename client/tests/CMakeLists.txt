cmake_minimum_required(VERSION 2.8.4)
project(wc_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(${PROJECT_NAME}_sources ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/check.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/clean.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/list.cpp)

set(${PROJECT_NAME}_headers ${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h
                            ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/catch.hpp)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake;${CMAKE_MODULE_PATH}")

find_package(webdavclient CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_library(CURL_LIBRARY
    NAMES curl curllib libcurl_imp curllib_static
    HINTS "${CMAKE_PREFIX_PATH}/curl/lib"
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

target_link_libraries(${PROJECT_NAME} webdavclient pugixml curl)
