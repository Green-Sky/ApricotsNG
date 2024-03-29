cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(apricots_ng C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Bump up warning levels appropriately for clang, gcc & msvc
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

# either
option(USE_OPENAL "use openal" ON)
option(USE_MOJOAL "use mojoal" OFF)

if(USE_OPENAL AND USE_MOJOAL)
	message(FATAL_ERROR "you cant use both, openal AND mojoal!")
endif()

if(NOT EMSCRIPTEN)
	find_package(SDL2 REQUIRED)
endif()

if(USE_OPENAL)
	find_package(OpenAL REQUIRED)
endif()

set(AP_RES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res")

if(USE_MOJOAL)
	add_subdirectory("external/mojoal")
endif()

add_subdirectory("src")

