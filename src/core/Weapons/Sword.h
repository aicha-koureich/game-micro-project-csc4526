#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"

class Sword : public Weapon {
	private:

	public:
        explicit Sword(int damage);
        void attack(Entity& other) override;
        int getEffect() const override;
        AttackType getType() const override;
};

#endif