#include "Sword.h"

Sword::Sword(int damage, std::string swordName, int swordCost) : Weapon(damage, swordName, swordCost, AttackType::STRENGTH) {}

void Sword::attack(Enemy& target, float performance) {
  int damageToApply = std::round(effect * performance);
  target.takeDamage(damageToApply);
}