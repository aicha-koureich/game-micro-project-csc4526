#ifndef FEATHER_H
#define FEATHER_H

#include "Weapon.h"

class Feather : public Weapon {
	private:

    public:
        explicit Feather(int power);
        int getEffect() const override;
        AttackType getType() const override;
        int attack(Entity& other) override;

};

#endif