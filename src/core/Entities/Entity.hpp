#include "AttackType.hpp"


class Entity {
 protected:
  int healthPoints;
 public:
  const int getHealthPoints();
  virtual void takeDamage(const Entity& attacker, int attackRes)=0;
  virtual void attack(const Entity& target, AttackType type)=0;
  Entity();
  virtual ~Entity();
};