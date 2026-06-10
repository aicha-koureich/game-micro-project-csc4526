#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include "Weapons/Weapon.h"

class Factory {
 public:
     virtual ~Factory() = default;
	 virtual std::unique_ptr<Weapon> createWeapon(int value) = 0;
 
};

class StrengthFactory : public Factory {
	std::unique_ptr<Weapon> createWeapon(int value) override;
};

class EloquenceFactory : public Factory {
  std::unique_ptr<Weapon> createWeapon(int value) override;
};

#endif
