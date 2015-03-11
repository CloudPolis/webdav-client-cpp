cmake_minimum_required(VERSION 2.8.4)
project(webdavclient)

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(GNUInstallDirs)
mark_as_advanced(CLEAR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_INCLUDEDIR)

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

add_definitions(-DUSE_SSLEAY -DUSE_OPENSSL)

if(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})
else()
    add_definitions(-DCURL_STATICLIB)
    add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})
endif()

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-config 
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES ${${PROJECT_NAME}_headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/webdav)
install(EXPORT ${PROJECT_NAME}-config DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
