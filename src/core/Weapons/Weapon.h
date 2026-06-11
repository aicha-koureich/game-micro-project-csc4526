#ifndef WEAPON_H
#define WEAPON_H

#include "Weapons/Weapon.h"
#include "AttackType.hpp"

class Weapon {
	public:
		virtual ~Weapon() = default;

		virtual int getEffect() const = 0;
		virtual AttackType getType() const = 0;
};

#endif