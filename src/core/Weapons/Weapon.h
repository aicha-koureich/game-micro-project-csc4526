#ifndef WEAPON_H
#define WEAPON_H

#include "Entity.hpp"


enum class AttackType {
	STRENGTH,
	ELOQUENCE
};

class Weapon {

	private:
		int weaponEffect;
        std::string name;
        int cost;
        AttackType type;

	public:
		virtual ~Weapon() = default;
		virtual int getEffect() const = 0;
		virtual AttackType getType() const = 0;
        virtual int attack(Entity& other) = 0;
};

#endif