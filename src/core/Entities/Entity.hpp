#ifndef ATTACKTYPE_HPP
#define ATTACKTYPE_HPP

#include "AttackType.hpp"

class Entity {
 protected:
  int healthPoints;

 public:

  virtual void takeDamage(AttackType type, int attackRes) = 0;
  virtual void attack(const Entity& target, AttackType type) = 0;
  virtual float computeDamage() = 0;
  Entity(int hp) : healthPoints(hp) {}
  virtual ~Entity() = default;
  int getHealthPoints() const { return healthPoints; }
};
//l
#endif

