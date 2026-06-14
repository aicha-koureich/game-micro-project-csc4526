#include "Sword.h"

Sword::Sword(int damage) : weaponEffect(damage) {}

int Sword::getEffect() const { return weaponEffect; }

AttackType Sword::getType() const { return AttackType::Force; }

void Sword::attack(Entity& other) { return; }