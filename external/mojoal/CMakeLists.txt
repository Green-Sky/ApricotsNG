cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

add_library(mojoal
	AL/al.h
	AL/alc.h
	mojoal.c
)

target_include_directories(mojoal PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if(EMSCRIPTEN)
	set_target_properties(mojoal PROPERTIES COMPILE_FLAGS "-s USE_SDL=2 -s USE_PTHREADS=1")
	set_target_properties(mojoal PROPERTIES LINK_FLAGS "-s USE_SDL=2 -s USE_PTHREADS=1")
else()
	target_include_directories(mojoal PUBLIC "${SDL2_INCLUDE_DIR}")
	target_link_libraries(mojoal ${SDL2_LIBRARY})
endif()


