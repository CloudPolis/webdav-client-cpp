cmake_minimum_required(VERSION 3.1)
project(webdavclient)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)
option(BUILD_TESTS "Build tests for webdavclient" OFF)
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
include_directories(${PUGIXML_INCLUDE_DIR})

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
include(CPack)
