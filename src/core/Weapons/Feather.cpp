#include "Feather.h"

Feather::Feather(int power) : eloquencePower(power) {}

int Feather::getEffect() const{ return eloquencePower; }

AttackType Feather::getType() const { return AttackType::ELOQUENCE; }