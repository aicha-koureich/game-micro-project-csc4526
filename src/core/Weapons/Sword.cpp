#include "Sword.h"

Sword::Sword(int damage, std::string swordName, int swordCost) : Weapon(damage, swordName, swordCost, AttackType::STRENGTH) {}

void Sword::attack(Entity& target, float performance) {
  int damageToApply = std::round(effect * performance);
  target.receiveAttack(damageToApply);
}