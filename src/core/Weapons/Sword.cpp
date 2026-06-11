#include "Sword.h"

Sword::Sword(int damage) : swordDamage(damage) {}

int Sword::getEffect() const { return swordDamage; }

AttackType Sword::getType() const { return AttackType::STRENGTH; }