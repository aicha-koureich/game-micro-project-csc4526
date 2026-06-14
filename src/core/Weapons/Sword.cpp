#include "Sword.h"
² Sword::Sword(int damage, std::string swordName, int swordCost) : Weapon(damage, swordName, swordCost, AttackType::STRENGTH) {}

Sword::Sword(WeaponType type, const std::string& name, int weaponEffect, int cost) : Weapon(type, name, weaponEffect, cost) {}

int Sword::attack(Entity& target, float performance) {
  return effect * performance;	
}