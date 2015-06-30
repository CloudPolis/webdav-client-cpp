cmake_minimum_required(VERSION 2.8)
project(Webdavclient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(cmake/FindCPM.cmake)
CPM_AddModule("pugixml"
  GIT_REPOSITORY "https://github.com/designerror/cpm-pugixml")
include_directories(${CPM_INCLUDE_DIRS})

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)
option(STATIC_RUNTIME_LIBRARY "Static runtime library" ON)
option(UNICODE "Character set is UNICODE" ON)
option(BUILD_TESTS_FOR_${PROJECT_NAME} "Build tests" OFF)

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

if(UNICODE)
    add_definitions(-D_UNICODE -DUNICODE)
endif()

include_directories(./include/)

file(GLOB ${PROJECT_NAME}_sources "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

set(${PROJECT_NAME}_headers ${CMAKE_CURRENT_SOURCE_DIR}/include/client.hpp)

if(WIN32 AND MSVC AND NOT BUILD_SHARED_LIBS)
    SET(CMAKE_MODULE_PATH "${CMAKE_ROOT}/Modules")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
    include(FindStaticOpenSSL)
else()
    find_package(OpenSSL)
endif()
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

if(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})
else()
    add_definitions(-DCURL_STATICLIB)
    add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})
endif()

if(UNIX)
    target_link_libraries(${PROJECT_NAME} pthread ${CPM_LIBRARIES} ${OPENSSL_LIBRARIES} ${CURL_LIBRARY})
else()
    target_link_libraries(${PROJECT_NAME} ${CPM_LIBRARIES} ${OPENSSL_LIBRARIES} ${CURL_LIBRARY})
    # ws2_32
endif()

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Config
    ARCHIVE DESTINATION lib/static
    LIBRARY DESTINATION lib
)
install(FILES ${${PROJECT_NAME}_headers} DESTINATION include)

install(EXPORT ${PROJECT_NAME}Config DESTINATION cmake)

configure_file(${PROJECT_SOURCE_DIR}/cmake/ProjectConfig-include.cmake.in
               ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}Config-include.cmake)

install(FILES ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}Config-include.cmake 
        DESTINATION cmake)

if(BUILD_TESTS_FOR_${PROJECT_NAME})
    add_subdirectory(tests)
endif()
