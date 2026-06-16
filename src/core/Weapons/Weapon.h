#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <cmath>
#include "Entities/Entity.hpp"

/* - les effets des armes sont sous une variable weaponEffect
   - Les getters font la meme chose pour sword et feather donc pas besoin qu'ils soient virtuels pures 
   - J'ai ajout� nom, comme ca ils pourront apparaitre dans le catalogue et le jeu en g�n�ral
   - AttackType a plus trop d'utilit� en fait, on sait qu'une feather c'est eloq, et la logique d'attaque est dans l'arme mtn donc info redondante*/


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
        virtual void attack(Entity& target, float performance) = 0;
};

#endif