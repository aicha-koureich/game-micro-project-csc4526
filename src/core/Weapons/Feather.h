#ifndef FEATHER_H
#define FEATHER_H

#include "Weapon.h"

class Feather : public Weapon {
 public:
  explicit Feather( WeaponType type, const std::string& name, int weaponEffect, int cost);
  ~Feather() override = default;
  int attack(Entity&);
}; 

#endif