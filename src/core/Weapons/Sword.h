#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"

class Sword : public Weapon {
 public:
  explicit Sword(WeaponType type, const std::string& name, int weaponEffect, int cost);
  ~Sword() override = default;
  int attack(Entity&)override;
};

#endif