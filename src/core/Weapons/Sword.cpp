#include "Sword.h"

Sword::Sword(int damage) : weaponEffect(damage) {}

int Sword::getEffect() const { return weaponEffect; }

AttackType Sword::getType() const { return AttackType::STRENGTH; }

int Sword::attack(Entity& other) { return 0; }