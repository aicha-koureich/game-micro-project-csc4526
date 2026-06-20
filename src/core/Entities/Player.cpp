#include <iostream>
#include "Player.hpp"


Player::Player(int maxHp, int money, float size, int defense, Weapon* playerWeapon)
    : Entity(maxHp),
      totalMoney(money),
      noseSize(size),
      baseDefense(defense),
      currentWeapon(playerWeapon) {}



void Player::increaseNoseSize(int enemyLevel) { 
    float noseScore = healthPoints * 0.1f; 
    noseSize += noseScore;

    maxHealthPoints += 10;
    baseDefense += (2 * enemyLevel);

}

void Player::addMoney(int amount) { totalMoney += amount; }

void Player::restoreHealth() { healthPoints = maxHealthPoints; }


void Player::pickWeapon(size_t idx) { 
    if (idx < weaponInventory.size() && weaponInventory[idx].get() != nullptr) {
        currentWeapon = weaponInventory[idx].get();
    }
     
}

bool Player::purchaseWeapon(std::unique_ptr<Weapon>& newWeapon) {
  int weaponCost = newWeapon->getCost();
  if (totalMoney >= weaponCost) {
    weaponInventory.push_back(std::move(newWeapon));
    totalMoney -= weaponCost;
    return true;
  } else {
    printf("Not enough money to buy this weapon !\n");
    return false;
  }
    
}


void Player::takeDamage(int attackRes){
  int finalDamage = std::max(1, attackRes - baseDefense);
  healthPoints = std::max(0, healthPoints - finalDamage);
}

void Player::playerAttack(Enemy& target, float performance) {
    currentWeapon->attack(target, performance);
}
