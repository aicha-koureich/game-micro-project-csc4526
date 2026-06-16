#include <iostream>
#include "Player.hpp"


Player::Player(int hp)
    : Entity(hp),
      totalMoney(0),
      noseSize(0),
      speed(1.0f),
      baseDefense(5),
      eloquenceEffect(0),
      currentWeapon(nullptr) {}


void Player::takeDamage(int attackRes){
  int finalDamage = attackRes - baseDefense;
  healthPoints = std::max(0, finalDamage);
}

void Player::playerAttack(Entity& target, float performance) {
    currentWeapon->attack(target, performance);
}



    
