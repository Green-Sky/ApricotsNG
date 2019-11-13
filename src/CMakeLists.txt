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

if(USE_OPENAL OR USE_MOJOAL)
	target_compile_definitions(apricots_ng PUBLIC AP_AUDIO_OPENAL)
endif()

if(USE_MOJOAL)
	target_link_libraries(apricots_ng mojoal)
endif()

if(EMSCRIPTEN)
	if(USE_OPENAL)
		set_target_properties(apricots_ng PROPERTIES COMPILE_FLAGS "-s USE_SDL=2")
		set_target_properties(apricots_ng PROPERTIES LINK_FLAGS "-s USE_SDL=2 -s --embed-file ${AP_RES_DIR}@res/")
	elseif(USE_MOJOAL)
		#mojoal uses mutexes
		set_target_properties(apricots_ng PROPERTIES COMPILE_FLAGS "-s USE_SDL=2 -s USE_PTHREADS=1")
		set_target_properties(apricots_ng PROPERTIES LINK_FLAGS "-s USE_SDL=2 -s USE_PTHREADS=1 --embed-file ${AP_RES_DIR}@res/")
	endif()
else()
	target_include_directories(apricots_ng PUBLIC "${SDL2_INCLUDE_DIR}")
	target_link_libraries(apricots_ng ${SDL2_LIBRARY})
endif()

if(USE_OPENAL)
	target_include_directories(apricots_ng PUBLIC "${OPENAL_INCLUDE_DIR}")
	target_link_libraries(apricots_ng ${OPENAL_LIBRARY})
endif()

