
cmake_minimum_required(VERSION 2.6)
project(HelloWorld)

set( SOURCES main.cpp)
#set( HEADERS )

# SDL STUFF
include(FindPkgConfig)
pkg_search_module(SDL REQUIRED sdl)

find_package(OpenGL REQUIRED)

#do we need Cocoa?

include_directories(${SDL_INCLUDE_DIRS})

add_executable(
	HelloWorld
	WIN32
	MACOSX_BUNDLE
	${SOURCES}
)


target_link_libraries(
	HelloWorld
	${OPENGL_LIBRARIES}
	${SDL_LIBRARIES}
)