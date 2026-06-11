#include "Factory.h"
#include "Weapons/Sword.h"
#include "Weapons/Feather.h"

std::unique_ptr<Weapon> StrengthFactory::createWeapon(int value) {
  return std::make_unique<Sword>(value);
}

std::unique_ptr<Weapon> EloquenceFactory::createWeapon(int value) {
  return std::make_unique<Feather>(value);
}

