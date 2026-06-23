#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <vector>
#include "Enemy.hpp"
#include "Weapons/Weapon.h"
#include "Item/Item.hpp"

using namespace std;

class Player : public Entity {
 private:
  int totalMoney;
  float noseSize;
  int mana;
  int maxMana;
  int baseDefense;
  Weapon* currentWeapon;
  vector<unique_ptr<Weapon>> weaponInventory;
  vector<std::unique_ptr<Item>> itemInventory;

 public:
  Player(int maxHp, int money, float size, int maxMana, int defense, Weapon* playerWeapon);
  ~Player() override = default;

  // Getters
  int getTotalMoney() const { return totalMoney; }

  float getNoseSize() const { return noseSize; }

  int getMana() const { return mana; }

  int getMaxMana() const { return maxMana; }

  int getBaseDefense() const { return baseDefense; }
 
  Weapon* getCurrentWeapon() const { return currentWeapon; }

  const vector<std::unique_ptr<Weapon>>& getWeaponInventory() const {
    return weaponInventory;
  }

  //EndFight bonus
  void increaseNoseSize(int enemyLevel);
  void addMoney(int amount);
  void restoreHealth();

  //Weapon Methods  
  void pickWeapon(size_t idx);
  bool purchaseWeapon(std::unique_ptr<Weapon>&);

  //Attack Methods
  void takeDamage(int attackRes) override;
  void playerAttack(Enemy& target, float performance);

  //Mana Methods
  void reduceMana(int cost) { mana = std::max(0, mana - cost); }
  void regenMana(int amount) { mana = std::min(maxMana, mana + amount); }

  
  //Items Methodes
  //void useItem(size_t idx);
  bool purchaseItem(std::unique_ptr<Item>&);
  const vector<std::unique_ptr<Item>>& getItemInventory() const {
    return itemInventory;
  }
  void setHealthPoints(int buffedHp){healthPoints = buffedHp;}
};
#endif