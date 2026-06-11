#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include "AttackType.hpp"
#include "Entity.hpp"
#include "Weapon.h"
using namespace std;

class Player : public Entity {
 private:
  AttackType currentAttack;
  int baseDamage;
  int baseDefense;
  int noseSize;
  float speed;
  bool isBlocking;
  unique_ptr<Weapon> currentWeapon;

 public:
  void takeDamage(AttackType type, int attackRes) override;
  void attack(const Entity& target, AttackType type) override;
  float computeDamage() override;
  void setAttackType();
  AttackType getCurrentAttackType();
  Player(int hp);
  ~Player() override = default;
};
#endif