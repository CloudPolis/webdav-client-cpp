#***************************************************************************
#                         __    __   _____       _____
#   Project              |  |  |  | |     \     /  ___|
#                        |  |__|  | |  |\  \   /  /
#                        |        | |  | )  ) (  (     
#                        |   /\   | |  |/  /   \  \___
#                         \_/  \_/  |_____/     \_____|
#
# Copyright (C) 2016, The WDC Project, <designerror@yandex.ru>, et al.
#
# This software is licensed as described in the file LICENSE, which
# you should have received as part of this distribution. 
#
# You may opt to use, copy, modify, merge, publish, distribute and/or sell
# copies of the Software, and permit persons to whom the Software is
# furnished to do so, under the terms of the LICENSE file.
#
# This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
# KIND, either express or implied.
#
############################################################################

cmake_minimum_required(VERSION 3.1)
project(wdc)

set(WDC_VERSION_MAJOR 1)
set(WDC_VERSION_MINOR 0)
set(WDC_VERSION_PATCH 1)
set(WDC_VERSION ${WDC_VERSION_MAJOR}.${WDC_VERSION_MINOR}.${WDC_VERSION_PATCH})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)
option(BUILD_TESTS "Build tests" OFF)
option(BUILD_PKGCONFIG "Build in PKGCONFIG mode" OFF)

option(MSVC_SHARED_RT "Shared runtime library" ON)
option(USE_EXTERNAL_PUGIXML "Use external pugixml" OFF)

if(MSVC AND (NOT MSVC_SHARED_RT))
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

set(${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/)
include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})
file(GLOB ${PROJECT_NAME}_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp")

set(${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/)

if(MSVC AND NOT MSVC_SHARED_RT)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
    include(FindStaticOpenSSL)
else()
    find_package(OpenSSL REQUIRED)
endif()

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

if (USE_EXTERNAL_PUGIXML)
find_package(PugiXML)
else()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
# YOU MUST SET PUGIXML_HOME
find_package(PugiXML REQUIRED)
endif()
include_directories(${PUGIXML_INCLUDE_DIRS})

if(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES})
else()
    add_definitions(-DCURL_STATICLIB)
    add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCES})
endif()

if(UNIX)
set(DEPENDS_LIBRARIES ${PUGIXML_LIBRARIES} ${OPENSSL_LIBRARIES} ${CURL_LIBRARY} pthread)
elseif(MSVC)
set(DEPENDS_LIBRARIES ${PUGIXML_LIBRARIES} ${OPENSSL_LIBRARIES} ${CURL_LIBRARY} ws2_32)
endif()

target_link_libraries(${PROJECT_NAME} ${DEPENDS_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Config
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(DIRECTORY ${${PROJECT_NAME}_INCLUDE_DIRS} DESTINATION include)

install(EXPORT ${PROJECT_NAME}Config DESTINATION cmake)

configure_file(${PROJECT_SOURCE_DIR}/cmake/ProjectConfig-include.cmake.in
               ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}Config-include.cmake @ONLY)

if(BUILD_PKGCONFIG)
	configure_file(scripts/wdc.pc.in ${PROJECT_BINARY_DIR}/wdc.pc @ONLY)
	install(FILES ${PROJECT_BINARY_DIR}/wdc.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
endif()	       

install(FILES ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}Config-include.cmake 
        DESTINATION cmake)

if(BUILD_TESTS)
	enable_testing()
	file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
	add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
	target_link_libraries(check ${PROJECT_NAME} ${DEPENDS_LIBRARIES})
	add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes") 
endif()

include(CPackConfig.cmake)
