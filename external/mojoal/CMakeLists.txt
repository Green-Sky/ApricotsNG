cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

add_library(mojoal
	AL/al.h
	AL/alc.h
	mojoal.c
)

target_include_directories(mojoal PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(mojoal PUBLIC "${SDL2_INCLUDE_DIR}")

target_link_libraries(mojoal ${SDL2_LIBRARY})


