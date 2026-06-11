#ifndef ATTACKTYPE_HPP
#define ATTACKTYPE_HPP

#include "AttackType.hpp"

class Entity {
 protected:
  int healthPoints;

 public:
<<<<<<< HEAD
  const int getHealthPoints();
  virtual void takeDamage(const Entity& attacker, int attackRes)=0;
  virtual void attack(const Entity& target, AttackType type)=0;
  Entity();
  virtual ~Entity();
};
=======
  virtual void takeDamage(const Entity& attacker, int attackRes) = 0;
  virtual void attack(const Entity& target, AttackType type) = 0;
  Entity(int hp) : healthPoints(hp) {}
  virtual ~Entity() = default;
  int getHealthPoints() const { return healthPoints; }
};
//l
#endif
>>>>>>> b6fb432a40313eff3a3af5dae60500b599181406
