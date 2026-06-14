#ifndef ATTACKTYPE_HPP
#define ATTACKTYPE_HPP

#include "AttackType.hpp"

class Entity {
 protected:
  int healthPoints;

 public:

  virtual void takeDamage(int attackRes) = 0;
  virtual int attack(const Entity& target) = 0;
  Entity(int hp) : healthPoints(hp) {}
  virtual ~Entity() = default;
  int getHealthPoints() const { return healthPoints; }
};

#endif

