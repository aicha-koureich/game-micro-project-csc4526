add_library(lib_core
        Game.cpp Game.hpp
	RoundTarget.cpp RoundTarget.hpp
        myMain.cpp myMain.h
)

target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC sfml-graphics)
