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

cmake_minimum_required(VERSION 3.3)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.19.123.tar.gz"
    SHA1 "57d07480686f82ddc916a5980b4f2a18e5954c2b"
)

set(WDC_VERSION_MAJOR 1)
set(WDC_VERSION_MINOR 1)
set(WDC_VERSION_PATCH 1)
set(WDC_VERSION ${WDC_VERSION_MAJOR}.${WDC_VERSION_MINOR}.${WDC_VERSION_PATCH})

project(WDC VERSION ${WDC_VERSION})

#include($ENV{POLLY_ROOT}/analyze.cmake OPTIONAL)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_EXAMPLES "Build Examples" OFF)
option(BUILD_PKGCONFIG "Build in PKGCONFIG mode" OFF)

option(WDC_VERBOSE "Print verbose information" OFF)

hunter_add_package(OpenSSL)
find_package(OpenSSL REQUIRED)
hunter_add_package(CURL)
find_package(CURL CONFIG REQUIRED)
hunter_add_package(pugixml)
find_package(pugixml CONFIG REQUIRED)

file(GLOB ${PROJECT_NAME}_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(libwdc ${${PROJECT_NAME}_SOURCES})
set_target_properties(libwdc PROPERTIES PREFIX "")
set_target_properties(libwdc PROPERTIES IMPORT_PREFIX "")
if(WDC_VERBOSE)
  target_compile_definitions(libwdc PUBLIC WDC_VERBOSE=1)
endif()

target_link_libraries(libwdc OpenSSL::SSL OpenSSL::Crypto CURL::libcurl pugixml)

target_include_directories(libwdc PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Install

set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

set(CONFIG_INSTALL_DIR "lib/cmake/${PROJECT_NAME}")
set(INCLUDE_INSTALL_DIR "include")

set(VERSION_CONFIG "${GENERATED_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(PROJECT_CONFIG "${GENERATED_DIR}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(NAMESPACE "${PROJECT_NAME}::")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${VERSION_CONFIG}" COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in"
    "${PROJECT_CONFIG}"
     INSTALL_DESTINATION "${CONFIG_INSTALL_DIR}"
)

install(TARGETS libwdc
    EXPORT "${TARGETS_EXPORT_NAME}"
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)

install(
  FILES "${PROJECT_CONFIG}" "${VERSION_CONFIG}"
  DESTINATION "${CONFIG_INSTALL_DIR}"
  )

install(EXPORT "${TARGETS_EXPORT_NAME}" 
    NAMESPACE "${NAMESPACE}" 
    DESTINATION "${CONFIG_INSTALL_DIR}")

if(BUILD_PKGCONFIG)
	configure_file(scripts/wdc.pc.in ${PROJECT_BINARY_DIR}/wdc.pc @ONLY)
	install(FILES ${PROJECT_BINARY_DIR}/wdc.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
endif()	       

if(BUILD_TESTS)
    hunter_add_package(Boost COMPONENTS system filesystem)
    find_package(Boost CONFIG REQUIRED system filesystem)
    hunter_add_package(Catch)
    find_package(Catch CONFIG REQUIRED)

	enable_testing()

	file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
	add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
	target_link_libraries(check libwdc Catch::Catch Boost::filesystem Boost::system)

	add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes") 
endif()

if(BUILD_EXAMPLES)
    file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*/*.cpp")
    foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
        get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
        set(EXAMPLE_TARGET_NAME example_${EXAMPLE_NAME})
        add_executable(${EXAMPLE_TARGET_NAME} ${EXAMPLE_SOURCE})
        target_link_libraries(${EXAMPLE_TARGET_NAME} libwdc)
        set_target_properties(${EXAMPLE_TARGET_NAME} PROPERTIES OUTPUT_NAME ${EXAMPLE_NAME})
        install(TARGETS ${EXAMPLE_TARGET_NAME}
                RUNTIME DESTINATION bin
                )
    endforeach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
endif()

include(CPackConfig.cmake)
