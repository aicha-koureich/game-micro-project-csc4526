add_library(lib_core
        "Entities/Enemy.hpp" "Entities/Enemy.cpp"
        "Entities/Player.hpp" "Entities/Player.cpp"
        "Entities/Entity.hpp"
        "Weapons/Feather.h" "Weapons/Feather.cpp"
        "Weapons/Sword.h" "Weapons/Sword.cpp"
        "Weapons/Weapon.h"

)

target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC sfml-graphics)