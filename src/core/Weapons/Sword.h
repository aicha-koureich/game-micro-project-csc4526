#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"

class Sword : public Weapon {
	private:
		int swordDamage;

	public:
        explicit Sword(int damage);
         int getEffect() const override;
        AttackType getType() const override;
};

#endif