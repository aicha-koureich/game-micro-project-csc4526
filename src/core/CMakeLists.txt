add_library(lib_core
        Game.cpp Game.hpp
	RoundTarget.cpp RoundTarget.hpp
        myMain.cpp myMain.h
 "Factories/Factory.h"  "Weapons/Weapon.h"  "Weapons/Sword.h" "Weapons/Sword.cpp"  "Weapons/Feather.h" "Weapons/Feather.cpp"    "Factories/Factory.cpp")

target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC sfml-graphics)
