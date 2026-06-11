#include "AttackType.hpp"

class Entity {
 protected:
  int healthPoints;

 public:
  virtual void takeDamage(const Entity& attacker, AttackType type) = 0;
  virtual void attack(const Entity& target, AttackType type) = 0;
  Entity(int hp) : healthPoints(hp) {}
  virtual ~Entity() = default;
  int getHealthPoints() const { return healthPoints; }
};