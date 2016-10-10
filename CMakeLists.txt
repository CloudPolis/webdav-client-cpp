cmake_minimum_required(VERSION 2.8)
project(webdavclient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

option(BUILD_SHARED_LIBS "Build shared instead of static library" ON)
option(MSVC_SHARED_RT "Shared runtime library" ON)
option(UNICODE "Character set is UNICODE" ON)
option(BUILD_TESTS_FOR_${PROJECT_NAME} "Build tests" ON)

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

if(UNICODE)
    add_definitions(-D_UNICODE -DUNICODE)
endif()

set(${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/)
include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})
file(GLOB ${PROJECT_NAME}_sources "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp")

set(${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/)

if(MSVC AND NOT MSVC_SHARED_RT)
    SET(CMAKE_MODULE_PATH "${CMAKE_ROOT}/Modules")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
    include(FindStaticOpenSSL)
else()
    find_package(OpenSSL)
endif()
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

find_package(pugixml REQUIRED)
include_directories(${pugixml_INCLUDE_DIRS})

if(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})
else()
    add_definitions(-DCURL_STATICLIB)
    add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})
endif()

if(UNIX)
set(DEPENDS_LIBRARIES ${pugixml_LIBRARIES} ${OPENSSL_LIBRARIES} ${CURL_LIBRARY} pthread)
elseif(MSVC)
set(DEPENDS_LIBRARIES ${pugixml_LIBRARIES} ${OPENSSL_LIBRARIES} ${CURL_LIBRARY} ws2_32)
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

install(FILES ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}Config-include.cmake 
        DESTINATION cmake)

if(BUILD_TESTS_FOR_${PROJECT_NAME})
    add_subdirectory(tests)
endif()
