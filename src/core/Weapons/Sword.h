#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"
#include "Factories/Factory.h"

class Sword : public Weapon {
 private:
  static bool registered;

	public:
        Sword(int damage, std::string swordName, int swordCost);
        void attack(Enemy& target, float performance) override;
};

#endif