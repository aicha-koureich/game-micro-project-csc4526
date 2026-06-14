#include "Sword.h"
² Sword::Sword(int damage, std::string swordName, int swordCost) : Weapon(damage, swordName, swordCost, AttackType::STRENGTH) {}


int Sword::attack(Entity& target, float performance) {
  return effect * performance;	
}