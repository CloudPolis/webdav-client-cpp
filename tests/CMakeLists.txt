cmake_minimum_required(VERSION 2.8)
<<<<<<< HEAD
set(TESTS_FOR_PROJECT Webdavclient)
project(Tests_${TESTS_FOR_PROJECT})
=======
project(Tests)
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)
option(STATIC_RUNTIME_LIBRARY "Static runtime library" ON)

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

<<<<<<< HEAD
if(UNICODE)
    add_definitions(-D_UNICODE -DUNICODE)
endif()

include(cmake/FindCPM.cmake)
#CPM_AddModule("cpm-catch"
#  GIT_REPOSITORY "https://github.com/designerror/cpm-catch")
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/)
include_directories(${CPM_INCLUDE_DIRS})

file(GLOB ${PROJECT_NAME}_sources "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

find_package(${TESTS_FOR_PROJECT} REQUIRED)
include_directories(${${TESTS_FOR_PROJECT}_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

target_link_libraries(${PROJECT_NAME} ${CPM_LIBRARIES} ${TESTS_FOR_PROJECT})

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${PROJECT_NAME} -s -r compact WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/..)
=======
include(cmake/FindCPM.cmake)
CPM_AddModule("cpm-catch"
  GIT_REPOSITORY "https://github.com/designerror/cpm-catch")
include_directories(${CPM_INCLUDE_DIRS})

file(GLOB ${PROJECT_NAME}_sources "${CMAKE_CURRENT_SOURCE_DIR}/client/*.cpp")

find_package(Webdavclient REQUIRED)
include_directories(${Webdavclient_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

target_link_libraries(${PROJECT_NAME} Webdavclient)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${PROJECT_NAME} -s -r compact WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/..)
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
