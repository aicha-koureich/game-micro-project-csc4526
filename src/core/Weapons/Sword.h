#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"

class Sword : public Weapon {
	private:

	public:
        explicit Sword(int damage);
        int getEffect() const override;
        AttackType getType() const override;
        int attack(Entity& other) override;
};

#endif