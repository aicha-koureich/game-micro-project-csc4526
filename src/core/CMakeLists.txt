add_library(lib_core
        "Others/Game.cpp" Others/Game.hpp
	"Others/RoundTarget.cpp" Others/RoundTarget.hpp
        "Others/myMain.cpp" "Others/myMain.h"
        "Others/Button.cpp" "Others/Button.hpp"
)

target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC sfml-graphics)