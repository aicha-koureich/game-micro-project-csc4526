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
    return false;
  }   
}
bool Player::purchaseItem(std::unique_ptr<Item>& newItem){
  int itemCost = newItem->getCost();
  if (totalMoney >= itemCost) {
    itemInventory.push_back(std::move(newItem));
    totalMoney -= itemCost;
    return true;
  } else {
    return false;
  }   
}
void Player::useItem(size_t idx) {
  if (idx >= itemInventory.size()) {
    std::cout << "Index d'item invalide !\n";
    return;
  }

  // On vérifie que la case n'est pas déjà vide (item deja utilisé)
  if (itemInventory[idx] == nullptr) {
    std::cout << "Aucun item a cet emplacement !\n";
    return;
  }
  // appel de la méthode used de l'item
  bool hasBeenUsed = itemInventory[idx]->used(*this);

  if (hasBeenUsed) {
    std::cout << "Item utilise avec succes !\n";
    itemInventory.erase(itemInventory.begin() + idx); //suppression propre sans case vide
  } else {
    std::cout << "L'item n'a pas pu etre utilise !\n";
  }
}

void Player::takeDamage(int attackRes){
  int finalDamage = std::max(1, attackRes - baseDefense);
  healthPoints = std::max(0, healthPoints - finalDamage);
}

void Player::playerAttack(Enemy& target, float performance) {
    currentWeapon->attack(target, performance);
}
