#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include "AttackType.hpp"
#include "Entity.hpp"
#include "Weapon.h"
using namespace std;

class Player : public Entity {
 private:
  AttackType currentAttackType;
  int baseDamage;
  int baseDefense;
  int noseSize;
  float speed;
  bool isBlocking;
  unique_ptr<Weapon> currentWeapon;

 public:
  Player(int hp);
  ~Player() override = default;
  AttackType getCurrentAttackType();
  Weapon* getCurrentWeapon();
  void setAttackType(AttackType type);
  void takeDamage(int attackRes) override;
  void attack(const Entity& target, AttackType playerAttack) override;
  void receiveAttack(int trueDamage, AttackType type) override;
  



};
#endif