#include <iostream>
#include "Player.hpp"


Player::Player(int hp)
    : Entity(hp),
      totalMoney(0),
      noseSize(0),
      baseDefense(15),
      currentWeapon(nullptr) {}



void Player::increaseNoseSize() { 
    float noseScore = healthPoints * 0.1f; 
    noseSize += noseScore;
}


void Player::pickWeapon(size_t idx) { 
    currentWeapon = weaponInventory[idx].get(); 
}

void Player::purchaseWeapon(std::unique_ptr<Weapon> newWeapon) {
  int weaponCost = newWeapon->getCost();
  if (totalMoney >= weaponCost) {
    weaponInventory.push_back(newWeapon);
    totalMoney -= weaponCost;
  }
    
}

void Player::takeDamage(int attackRes){
  int finalDamage = attackRes - baseDefense;
  healthPoints = std::max(0, finalDamage);
}

void Player::playerAttack(Entity& target, float performance) {
    currentWeapon->attack(target, performance);
}
