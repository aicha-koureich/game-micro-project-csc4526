#ifndef FEATHER_H
#define FEATHER_H

#include "Weapon.h"

class Feather : public Weapon {
	private:

    public:
        Feather(int eloquencePower, std::string featherName, int featherCost);

        int attack(Entity& target, float performance) override;

};

#endif