#include "Factory.h"

#include "Weapons/Feather.h"
#include "Weapons/Sword.h"

static std::unique_ptr<Weapon> createWeapon(const std::string& name) {return nullptr;}
