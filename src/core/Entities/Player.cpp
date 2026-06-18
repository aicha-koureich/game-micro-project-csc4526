#include <iostream>
#include "Player.hpp"


Player::Player(int hp, int money, float size, int defense, Weapon* playerWeapon)
    : Entity(hp),
      totalMoney(money),
      noseSize(size),
      baseDefense(defense),
      currentWeapon(playerWeapon) {}



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
    weaponInventory.push_back(std::move(newWeapon));
    totalMoney -= weaponCost;
  }
    
}

void Player::takeDamage(int attackRes){
  int finalDamage = attackRes - baseDefense;
  healthPoints = std::max(0, finalDamage);
}

void Player::playerAttack(Enemy& target, float performance) {
    currentWeapon->attack(target, performance);
}
