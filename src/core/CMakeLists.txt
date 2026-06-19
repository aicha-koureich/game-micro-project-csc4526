add_library(lib_core
        "Game/Game.cpp" Game/Game.hpp
        "Game/myMain.cpp" "Game/myMain.h"
        "Game/Button.cpp" "Game/Button.hpp"
)

target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC sfml-graphics)