#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include <pugixml.hpp>
#include "Weapons/Weapon.h"
/* - Factory va lire le XML avec toutes les armes et appeler le bon constructeur*/

class WeaponFactory {
 public:
     virtual ~WeaponFactory() = default;
	 virtual std::unique_ptr<Weapon> createWeapon(const std::string& name);
 
};

#endif
