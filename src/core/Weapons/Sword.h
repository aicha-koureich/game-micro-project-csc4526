#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"

class Sword : public Weapon {
	private:

	public:
        Sword(int damage, std::string swordName, int swordCost);
        void attack(Enemy& target, float performance) override;
};

#endif