cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

add_executable(apricots_ng
	./apricots.h
	./linkedlist.h
	./sampleio.h
	./shape.h
	./SDLfont.h

	./ai.cpp
	./all.cpp
	./apricots.cpp
	./collide.cpp
	./drak.cpp
	./drawall.cpp
	./fall.cpp
	./finish.cpp
	./game.cpp
	./init.cpp
	./sampleio.cpp
	./setup.cpp
	./shape.cpp
	./SDLfont.cpp
)

target_include_directories(apricots_ng PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(apricots_ng PUBLIC "${SDL2_INCLUDE_DIR}")

target_link_libraries(apricots_ng ${SDL2_LIBRARY})
target_link_libraries(apricots_ng mojoal)

target_compile_definitions(apricots_ng PUBLIC AP_AUDIO_OPENAL)

