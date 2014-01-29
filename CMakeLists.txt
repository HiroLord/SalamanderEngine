
cmake_minimum_required(VERSION 2.6)
project(HelloWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

IF(APPLE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework SDL2")
ENDIF(APPLE)

set( SOURCES lesson3.cpp)
#set( HEADERS )

# SDL STUFF
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ./)
find_package (SDL2_image REQUIRED)

find_package(OpenGL REQUIRED)

#do we need Cocoa?

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(
	HelloWorld
	WIN32
	MACOSX_BUNDLE
	${SOURCES}
)


target_link_libraries(
	HelloWorld
	${OPENGL_LIBRARIES}
	${SDL2_LIBRARIES}
	${SDL2_IMAGE_LIBRARY}
)
