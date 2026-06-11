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
  Player(int hp);
  ~Player() override = default;
  void takeDamage(int attackRes) override;
  void attack(const Entity& target, AttackType type) override;
  float computeDamage() override;
  void setAttackType();
  AttackType getCurrentAttackType();
  Weapon* getCurrentWeapon();


};
#endif