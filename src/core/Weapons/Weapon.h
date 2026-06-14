#ifndef WEAPON_H
#define WEAPON_H

#include <string>


class Entity;

enum class AttackType {
	STRENGTH,
	ELOQUENCE
};

class Weapon {

	protected:
		int effect;
        std::string name;
        int cost;
        AttackType type;

	public:
        Weapon(int weaponEffect, std::string weaponName, int weaponCost,
               AttackType attackType)
            : effect(weaponEffect),
              name(weaponName),
              cost(weaponCost),
              type(attackType) {}
		virtual ~Weapon() = default;

        int getEffect() {return effect;}
        AttackType getType() { return type; }
        virtual int attack(Entity& target, float performance) = 0;
};

#endif