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
#find_package(pugixml)
#if (PUGIXML_FOUND)
#else ()
#    message (STATUS "No PugiXML found")
#    return()
#endif()

#find_package(curl)
#if (CURL_FOUND)
#else ()
#    message (STATUS "No curl found")
#    return()
#endif()

#include_directories(${PUGIXML_INCLUDE_DIR})
#include_directories(${CURL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

#target_link_libraries(${PROJECT_NAME} webdavclient ${PUGIXML_LIBRARY} ${CURL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} webdavclient ${CURL_LIBRARIES})