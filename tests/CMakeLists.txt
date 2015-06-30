cmake_minimum_required(VERSION 2.8)
project(Tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)
option(STATIC_RUNTIME_LIBRARY "Static runtime library" ON)

include(cmake/FindCPM.cmake)
CPM_AddModule("cpm-catch"
  GIT_REPOSITORY "https://github.com/bcachet/cpm-catch")

if(STATIC_RUNTIME_LIBRARY)
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

file(GLOB ${PROJECT_NAME}_sources "${CMAKE_CURRENT_SOURCE_DIR}/client/*.cpp")

find_package(Webdavclient REQUIRED)
include_directories(${Webdavclient_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

target_link_libraries(${PROJECT_NAME} Webdavclient)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${PROJECT_NAME} -s -r compact WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/..)
