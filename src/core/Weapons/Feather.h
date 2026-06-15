#ifndef FEATHER_H
#define FEATHER_H

#include "Weapon.h"

enum class DebuffType { STRENGTH, DEFENSE };

class Feather : public Weapon {
	private:
        DebuffType currentChoice;

    public:
        Feather(int eloquencePower, std::string featherName, int featherCost);

        void attack(Entity& target, float performance) override;

        void setDebuffChoice(DebuffType choice);

};

#endif